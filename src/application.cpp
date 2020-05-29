#define _USE_MATH_DEFINES

#include "../include/application.h"
#include "../../include/geometrie/rayon.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"
#include "../../include/openGL/sceneOpenGL.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/forme.h"
#include "../../include/outils/image.h"

#include <string>
#include <math.h>
#include <algorithm>

Application::Application(int niveau, string fichierOutput, int nbSampling) {
    this->niveau = niveau;
    this->fichierOutput = fichierOutput;
    this->nbSampling = nbSampling;
}

Application::~Application() {

}

bool Application::estIllumine(Point& point, Lumiere& lumiere, vector<Forme*>& formes) {
    Vecteur vecteurIllumination = Point::creerVecteur(point, lumiere.position).unitaire();
    Rayon r = Rayon(point + _EPSILON_ * vecteurIllumination, vecteurIllumination);
    Point I;
    Vecteur N;

    for (Forme* forme : formes) {
        if (forme->intersection(r, I, N) && point.distance2(I) <= point.distance2(lumiere.position)) {
            return false;
        }
    }

    return true;
}

Couleur Application::illumination(Intersection& inter, Point& camera, Lumiere& lumiere, vector<Forme*>* formes) {
    Vecteur I = Point::creerVecteur(inter.intersection, lumiere.position).unitaire();
    Vecteur V = Point::creerVecteur(inter.intersection, camera).unitaire();
    Vecteur H = 0.5 * (I + V);

    if (nullptr != formes && !estIllumine(inter.intersection, lumiere, *formes)) {
        return Couleur();
    }

    /* Calcul de l'illumination selon le modèle de Blinn-Phong */

    double a = lumiere.intensite / (4 * M_PI * inter.intersection.distance2(lumiere.position));

    /* Composante rouge */
    double bR = inter.materiau.couleur.r * max<double>(inter.normale.prodScalaire(I), 0);
    double cR = inter.materiau.specularite.r * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);
    /* Composante verte */
    double bG = inter.materiau.couleur.g * max<double>(inter.normale.prodScalaire(I), 0);
    double cG = inter.materiau.specularite.g * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);
    /* Composante bleue */
    double bB = inter.materiau.couleur.b * max<double>(inter.normale.prodScalaire(I), 0);
    double cB = inter.materiau.specularite.b * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);

    double r = a * (bR + cR);
    double g = a * (bG + cG);
    double b = a * (bB + cB);

    return Couleur(r, g, b).clamp();
}

bool Application::interPlusProche(Rayon& r, vector<Forme*>& formes, Intersection& inter) {
    Point I;
    Vecteur N;
    double distance2PlusProche = -1;
    bool aIntersecte = false;

    for (auto* forme : formes) {
        if (forme->intersection(r, I, N)) {
            aIntersecte = true;
            double distance2 = r.origine.distance2(I);

            if (distance2PlusProche == -1 || distance2 < distance2PlusProche) {
                inter.materiau = forme->materiau;
                inter.intersection = I;
                inter.normale = N;
                distance2PlusProche = distance2;
            }
        }
    }

    return aIntersecte;
}

void Application::lancerRayonsAux(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, int pixelSampling, bool eclairage, bool ombrage, Couleur(*f)(Couleur nouveau, int iteration, Couleur ancien)) {
    for (unsigned int i = 0; i < scene.grille.resolution_h; i++) {
        for (unsigned int j = 0; j < scene.grille.resolution_l; j++) {
            Couleur couleurPixel;
            int rayonsLances = 0;

            do {
                Vecteur positionPixel = iteration <= 1 || pixelSampling <= 1 ? scene.grille.centrePixel(i, j) : scene.grille.pointAleatoirePixel(i, j);
                Rayon r(scene.camera.position, scene.grille.distance_focale * scene.camera.orientation + positionPixel);

                Intersection inter;
                if (interPlusProche(r, scene.formes, inter)) {
                    if (eclairage) {
                        Couleur moyenneIllumination = Couleur();
                        for (Lumiere& lumiere : scene.lumieres) {
                            moyenneIllumination = moyenneIllumination + illumination(inter, scene.camera.position, lumiere, ombrage ? &scene.formes : nullptr);
                        }
                        couleurPixel = couleurPixel + moyenneIllumination.clamp();
                    } else {
                        couleurPixel = couleurPixel + inter.materiau.couleur;
                    }
                } else {
                    couleurPixel = couleurPixel + Couleur();
                }

                rayonsLances++;
            } while (rayonsLances < pixelSampling);

            nouvelle.set(i, j, f(couleurPixel / max(pixelSampling, 1), iteration, ancienne.get(i, j)));
        }
    }
}

void Application::lancerRayons(Scene& scene, Image& image, bool eclairage, int pixelSampling, bool ombrage) {
    lancerRayonsAux(scene, 1, image, image, pixelSampling, true, ombrage,
        [](Couleur nouveau, int iteration, Couleur ancien) {
            return nouveau;
        });
}

void Application::lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, bool eclairage, int pixelSampling, bool ombrage) {
    lancerRayonsAux(scene, iteration, ancienne, nouvelle, pixelSampling, eclairage, ombrage, 
        [](Couleur nouveau, int iteration, Couleur ancien) {
            return (nouveau * (1.0 / iteration) + ancien * ((iteration - 1.0) / iteration));
        });
}

void Application::visualiserScene(Scene& scene) {
    SceneOpenGL sceneGL("Lancer de rayon interactif", scene.grille.resolution_l, scene.grille.resolution_h, scene, fichierOutput, niveau > 1, niveau > 2 ? nbSampling : 1, niveau > 2);

    // Initialisation de la scène
    if (sceneGL.initialiserFenetre() == false) {
        return;
    }

    if (sceneGL.initGL() == false) {
        return;
    }

    // Boucle Principale
    sceneGL.bouclePrincipale();
}

void Application::enregistrerImage(Scene& scene) {
    Image rendu(scene.grille.resolution_l, scene.grille.resolution_h);

    lancerRayons(scene, rendu, niveau > 1, niveau > 2 ? nbSampling : 1, niveau > 2);

    rendu.exportPPM(fichierOutput.c_str());
}