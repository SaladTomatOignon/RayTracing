#include "../../include/scene/ellipsoide.h"
#include "../../include/scene/sphere.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>
#include <iostream>

Ellipsoide::Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC, Materiau materiau) : Forme(materiau) {
    this->centre = Point(centre);
    this->rayonA = rayonA;
    this->rayonB = rayonB;
    this->rayonC = rayonC;

    initialiserMatricesTransformation();
}

Ellipsoide::Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC) : Ellipsoide(centre, rayonA, rayonB, rayonC, Materiau()) {

}

Ellipsoide::Ellipsoide(const Ellipsoide& Ellipsoide) : Ellipsoide(Ellipsoide.centre, Ellipsoide.rayonA, Ellipsoide.rayonB, Ellipsoide.rayonC, Ellipsoide.materiau) {

}

Ellipsoide::~Ellipsoide() {

}

Sphere* Ellipsoide::creerFormeCanonique() {
    // Sphère de rayon 1 centrée à l'origine.
    return new Sphere(Point(0, 0, 0), 1, Materiau(), true);
}

Sphere* Ellipsoide::getFormeCanonique() {
    return (Sphere*) formeCanonique;
}

Point Ellipsoide::getCentre() {
    return Point(centre);
}

void Ellipsoide::homothetieFormeCanonique() {
    Sphere* ellipsoideCanonique = getFormeCanonique();

    Md = Md * Matrice::mat_homothetie(ellipsoideCanonique->rayon / rayonA, ellipsoideCanonique->rayon / rayonB, ellipsoideCanonique->rayon / rayonC);
    Mi = Mi * Matrice::mat_homothetie(-ellipsoideCanonique->rayon / rayonA, -ellipsoideCanonique->rayon / rayonB, -ellipsoideCanonique->rayon / rayonC);
    Mn = Mn * Matrice::mat_homothetie((ellipsoideCanonique->rayon / rayonB) * (ellipsoideCanonique->rayon / rayonC), (ellipsoideCanonique->rayon / rayonA) * (ellipsoideCanonique->rayon / rayonC), (ellipsoideCanonique->rayon / rayonA) * (ellipsoideCanonique->rayon / rayonB));
}

void Ellipsoide::rotationFormeCanonique() {

}

void Ellipsoide::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Ellipsoide::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Sphere* ellipsoideCanonique = getFormeCanonique();
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!ellipsoideCanonique->intersection(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Vecteur(Mn * normale.unitaire()).unitaire();

    return true;
}