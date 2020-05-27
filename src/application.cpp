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

Couleur Application::illumination(Intersection inter, Point camera, Lumiere lumiere) {
    Vecteur I = Point::creerVecteur(inter.intersection, lumiere.position).unitaire();
    Vecteur V = Point::creerVecteur(inter.intersection, camera).unitaire();
    Vecteur H = 0.5 * V;

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

    return Couleur(r, g, b);
}

bool Application::interPlusProche(Rayon r, vector<Forme*> formes, Intersection& inter) {
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

void Application::lancerRayons(Scene& scene, Image& image, bool eclairage) {
    for (unsigned int i = 0; i < scene.grille.resolution_h; i++) {
        for (unsigned int j = 0; j < scene.grille.resolution_l; j++) {
            //Rayon r(scene.camera.position, Point::creerVecteur(scene.camera.position, scene.grille.at(i, j).getCentre()));

            Point A = scene.camera.position;
            double f = scene.grille.distance_focale;
            double tw = scene.grille.largeur;
            double th = scene.grille.hauteur;
            double resw = scene.grille.resolution_l;
            double resh = scene.grille.resolution_h;
            Vecteur u = scene.camera.orientation;
            Vecteur v = scene.grille.inclinaison_h;
            Vecteur w = scene.grille.inclinaison_v;

            if (i == 10 && j == 10) {
                double azerty = 1;
            }

            Rayon r(A, f * u - (tw / 2) * v + (th / 2) * w + (j + 1 / 2) * (tw / resw) * v - (i + 1 / 2) * (th / resh) * w);

            Intersection inter;
            if (interPlusProche(r, scene.formes, inter)) {
                if (eclairage) {
                    image[i][j] = illumination(inter, scene.camera.position, scene.lumieres[0]);
                } else {
                    image[i][j] = inter.materiau.couleur;
                }
            } else {
                image[i][j] = Couleur();
            }
        }
    }
}

void Application::lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle) {
    for (unsigned int i = 0; i < scene.grille.resolution_h; i++) {
        for (unsigned int j = 0; j < scene.grille.resolution_l; j++) {
            //Rayon r(scene.camera.position, Point::creerVecteur(scene.camera.position, scene.grille.at(i, j).getCentre()));

            Point A = scene.camera.position;
            double f = scene.grille.distance_focale;
            double tw = scene.grille.largeur;
            double th = scene.grille.hauteur;
            double resw = scene.grille.resolution_l;
            double resh = scene.grille.resolution_h;
            Vecteur u = scene.camera.orientation;
            Vecteur v = scene.grille.inclinaison_h;
            Vecteur w = scene.grille.inclinaison_v;

            if (i == 100 && j == 100) {
                double azerty = 1;
            }

            Rayon r(A, f * u - (tw / 2) * v + (th / 2) * w + (j + 1 / 2) * (tw / resw) * v - (i + 1 / 2) * (th / resh) * w);

            Intersection inter;
            Couleur couleur;
            if (interPlusProche(r, scene.formes, inter)) {
                couleur = illumination(inter, scene.camera.position, scene.lumieres[0]);
            } else {
                couleur = Couleur();
            }

            nouvelle[i][j] = couleur * (1.0 / iteration) + ancienne[i][j] * ((iteration - 1.0) / iteration);
        }
    }
}

void Application::visualiserScene(Scene& scene) {
    SceneOpenGL sceneGL("Lancer de rayon interactif", scene.grille.resolution_l, scene.grille.resolution_h, scene, fichierOutput);

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

    lancerRayons(scene, rendu, niveau > 1);

    rendu.exportPPM(fichierOutput.c_str());
}