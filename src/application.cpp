#define _USE_MATH_DEFINES
#define _MAX_RECURSIONS_ 16

#include "../include/application.h"
#include "../../include/geometrie/rayon.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"
#include "../../include/geometrie/matrice.h"
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

Couleur Application::couleurRefracteAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction, unsigned int iteration) {
    Couleur couleur;

    if (iteration > _MAX_RECURSIONS_ || inter.materiau.coeffRefraction <= 0) {
        return couleur;
    }

    Vecteur normaleRefraction = inter.normale; /* La normale peut être inversée selon si le rayon se trouve dans la forme ou pas. */
    
    double r;
    if (inter.incident.direction.prodScalaire(inter.normale) > 0) {
        /* On sort de la forme */
        r = 1 / inter.materiau.indiceRefraction;
        normaleRefraction = -1.0 * normaleRefraction;
    } else {
        /* On rentre dans la forme */
        r = inter.materiau.indiceRefraction;
    }

    double c = -normaleRefraction.prodScalaire(inter.incident.direction);
    if (1 - r * r * (1 - c * c) < 0) {
        return couleur;
    }

    Vecteur direction = (r * inter.incident.direction + (r * c - sqrt(1.0 - r * r * (1.0 - c * c))) * normaleRefraction).unitaire();
    Rayon refracte = Rayon(inter.intersection, direction);
    /* On décale un tout petit peu l'origine du rayon pour ne pas rentrer en intersection avec l'objet de départ */
    refracte.origine = refracte.origine + refracte.direction;

    Intersection intersectionRefraction;
    if (interPlusProche(refracte, formes, intersectionRefraction)) {
        couleur = illuminationFinale(intersectionRefraction, inter.intersection, lumieres, formes, eclairage, ombrage, reflet, refraction) * inter.materiau.coeffRefraction * (iteration == 1 && !inter.forme2D ? inter.materiau.coeffDiffusion : 1) +
                  couleurRefracteAux(intersectionRefraction, formes, lumieres, eclairage, ombrage, reflet, refraction, iteration + 1);
    }

    return couleur.clamp();
}

Couleur Application::couleurRefracte(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction) {
    return couleurRefracteAux(inter, formes, lumieres, eclairage, ombrage, reflet, refraction, 1);
}

Couleur Application::couleurReflechieAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction, unsigned int iteration) {
    Couleur couleur;

    if (iteration > _MAX_RECURSIONS_ || inter.materiau.reflexion <= 0 || inter.materiau.coeffRefraction > 0) {
        return couleur;
    }

    Vecteur direction = -1 * inter.incident.direction.rotationAxe(inter.normale, M_PI);
    Rayon reflechie = Rayon(inter.intersection, direction);
    /* On décale un tout petit peu l'origine du rayon pour ne pas rentrer en intersection avec l'objet de départ */
    reflechie.origine = reflechie.origine + _EPSILON_ * reflechie.direction;

    Intersection intersectionReflexion;
    if (interPlusProche(reflechie, formes, intersectionReflexion)) {
        couleur = illuminationFinale(intersectionReflexion, inter.intersection, lumieres, formes, eclairage, ombrage, reflet, refraction) * inter.materiau.reflexion +
                  couleurReflechieAux(intersectionReflexion, formes, lumieres, eclairage, ombrage, reflet, refraction, iteration + 1);
    }

    return couleur.clamp();
}

Couleur Application::couleurReflechie(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction) {
    return couleurReflechieAux(inter, formes, lumieres, eclairage, ombrage, reflet, refraction, 1);
}

bool Application::estIllumine(Point& point, Lumiere& lumiere, vector<Forme*>& formes) {
    Vecteur vecteurIllumination = Point::creerVecteur(point, lumiere.position).unitaire();
    /* On décale un tout petit peu l'origine du rayon pour ne pas rentrer en intersection avec l'objet de départ */
    Rayon r = Rayon(point + vecteurIllumination, vecteurIllumination);
    Point I;
    Vecteur N;

    for (Forme* forme : formes) {
        if (forme->intersection(r, I, N) && point.distance2(I) <= point.distance2(lumiere.position)) {
            return false;
        }
    }

    return true;
}

Couleur Application::illumination(Intersection& inter, Point& vue, Lumiere& lumiere, vector<Forme*>& formes, bool ombrage) {
    Vecteur I = Point::creerVecteur(inter.intersection, lumiere.position).unitaire();
    Vecteur V = Point::creerVecteur(inter.intersection, vue).unitaire();
    Vecteur H = 0.5 * (I + V);

    /* Calcul de l'ombrage */
    if (ombrage && !estIllumine(inter.intersection, lumiere, formes)) {
        return Couleur();
    }

    /* Calcul de l'illumination selon le modèle de Blinn-Phong */

    double a = lumiere.intensite / (4 * M_PI * inter.intersection.distance2(lumiere.position));

    /* Composante rouge */
    double bR = inter.materiau.couleur.r * inter.materiau.coeffDiffusion * max<double>(inter.normale.prodScalaire(I), 0);
    double cR = inter.materiau.specularite.r * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);
    /* Composante verte */
    double bG = inter.materiau.couleur.g * inter.materiau.coeffDiffusion * max<double>(inter.normale.prodScalaire(I), 0);
    double cG = inter.materiau.specularite.g * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);
    /* Composante bleue */
    double bB = inter.materiau.couleur.b * inter.materiau.coeffDiffusion * max<double>(inter.normale.prodScalaire(I), 0);
    double cB = inter.materiau.specularite.b * pow(max<double>(inter.normale.prodScalaire(H), 0), inter.materiau.brillance);

    double r = a * (bR + cR);
    double g = a * (bG + cG);
    double b = a * (bB + cB);

    return Couleur(r, g, b).clamp();
}

Couleur Application::illuminations(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, bool ombrage) {
    Couleur moyenneIllumination = Couleur();

    for (Lumiere& lumiere : lumieres) {
        moyenneIllumination = moyenneIllumination + illumination(inter, vue, lumiere, formes, ombrage);
    }

    return moyenneIllumination.clamp();
}

Couleur Application::illuminationFinaleAux(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, bool eclairage, bool ombrage, bool reflet, bool refraction, unsigned int iteration) {
    Couleur couleur;

    if (eclairage) {
        couleur = couleur + illuminations(inter, vue, lumieres, formes, ombrage);
    } else {
        couleur = couleur + inter.materiau.couleur;
    }

    if (reflet) {
        couleur = couleur + couleurReflechie(inter, formes, lumieres, eclairage, ombrage, reflet, refraction);
    }

    if (refraction) {
        couleur = couleur * inter.materiau.coeffDiffusion + couleurRefracte(inter, formes, lumieres, eclairage, ombrage, reflet, refraction);
    }

    return couleur;
}

Couleur Application::illuminationFinale(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, bool eclairage, bool ombrage, bool reflet, bool refraction) {
    return illuminationFinaleAux(inter, vue, lumieres, formes, eclairage, ombrage, reflet, refraction, 1);
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
                inter.incident = r;
                inter.forme2D = forme->forme2D;
                distance2PlusProche = distance2;
            }
        }
    }

    return aIntersecte;
}

void Application::lancerRayonsAux(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, int pixelSampling, bool eclairage, bool ombrage, bool reflet, bool refraction, Couleur(*f)(Couleur nouveau, int iteration, Couleur ancien)) {
    for (unsigned int i = 0; i < scene.grille.resolution_h; i++) {
        for (unsigned int j = 0; j < scene.grille.resolution_l; j++) {
            Couleur couleurPixel;
            int rayonsLances = 0;

            do {
                Vecteur positionPixel = iteration <= 1 || pixelSampling <= 1 ? scene.grille.centrePixel(i, j) : scene.grille.pointAleatoirePixel(i, j);
                Rayon r(scene.camera.position, scene.grille.distance_focale * scene.camera.orientation + positionPixel);

                Intersection inter;
                if (interPlusProche(r, scene.formes, inter)) {
                    couleurPixel = couleurPixel + illuminationFinale(inter, scene.camera.position, scene.lumieres, scene.formes, eclairage, ombrage, reflet, refraction);
                }

                rayonsLances++;
            } while (rayonsLances < pixelSampling);

            nouvelle.set(i, j, f(couleurPixel.clamp() / max(pixelSampling, 1), iteration, ancienne.get(i, j)));
        }
    }
}

void Application::lancerRayons(Scene& scene, Image& image, bool eclairage, int pixelSampling, bool ombrage, bool reflet, bool refraction) {
    lancerRayonsAux(scene, 1, image, image, pixelSampling, true, ombrage, reflet, refraction,
        [](Couleur nouveau, int iteration, Couleur ancien) {
            return nouveau;
        });
}

void Application::lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, bool eclairage, int pixelSampling, bool ombrage, bool reflet, bool refraction) {
    lancerRayonsAux(scene, iteration, ancienne, nouvelle, pixelSampling, eclairage, ombrage, reflet, refraction, 
        [](Couleur nouveau, int iteration, Couleur ancien) {
            return (nouveau * (1.0 / iteration) + ancien * ((iteration - 1.0) / iteration));
        });
}

void Application::visualiserScene(Scene& scene) {
    SceneOpenGL sceneGL("Lancer de rayon interactif", scene.grille.resolution_l, scene.grille.resolution_h, scene, fichierOutput, niveau > 1, niveau > 2 ? nbSampling : 1, niveau > 2, niveau > 2, niveau > 2);

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

    lancerRayons(scene, rendu, niveau > 1, niveau > 2 ? nbSampling : 1, niveau > 2, niveau > 2, niveau > 2);

    rendu.exportPPM(fichierOutput.c_str());
}