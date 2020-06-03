#include "../../include/scene/ellipsoide.h"
#include "../../include/scene/sphere.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>
#include <iostream>

Ellipsoide::Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC, Vecteur rotation, Materiau materiau) : Forme(centre, rotation, materiau) {
    this->rayonA = rayonA;
    this->rayonB = rayonB;
    this->rayonC = rayonC;

    initialiserMatricesTransformation();
}

Ellipsoide::Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC, Vecteur rotation) : Ellipsoide(centre, rayonA, rayonB, rayonC, Vecteur(), Materiau()) {

}

Ellipsoide::Ellipsoide(const Ellipsoide &ellipsoide) : Ellipsoide(ellipsoide.centre, ellipsoide.rayonA, ellipsoide.rayonB, ellipsoide.rayonC, ellipsoide.rotation, ellipsoide.materiau) {
}

Ellipsoide::~Ellipsoide() {

}

Sphere* Ellipsoide::creerFormeCanonique() {
    // Sph�re de rayon 1 centrée à l'origine.
    return new Sphere(Point(0, 0, 0), 1, Vecteur(0, 0, 0), Materiau(), true);
}

Sphere* Ellipsoide::getFormeCanonique() {
    return (Sphere*) formeCanonique;
}

Point Ellipsoide::getCentre() {
    return Point(centre);
}

void Ellipsoide::homothetieFormeCanonique() {
    Sphere* sphereCanonique = getFormeCanonique();

    Md = Md * Matrice::mat_homothetie(rayonA / sphereCanonique->rayon, rayonB / sphereCanonique->rayon, rayonC / sphereCanonique->rayon);
    Mi = Matrice::mat_homothetie(1 / (rayonA / sphereCanonique->rayon), 1 / (rayonB / sphereCanonique->rayon), 1 / (rayonC / sphereCanonique->rayon)) * Mi;
    Mn = Mn * Matrice::mat_homothetie((rayonB / sphereCanonique->rayon) * (rayonC / sphereCanonique->rayon), (rayonA / sphereCanonique->rayon) * (rayonC / sphereCanonique->rayon), (rayonA / sphereCanonique->rayon) * (rayonB / sphereCanonique->rayon));
}

void Ellipsoide::rotationFormeCanonique() {
    Md = Md * Matrice::mat_rotation_x(rotation.x);
    Mi = Matrice::mat_rotation_x(-rotation.x) * Mi;
    Mn = Mn * Matrice::mat_rotation_x(rotation.x);

    Md = Md * Matrice::mat_rotation_y(rotation.y);
    Mi = Matrice::mat_rotation_y(-rotation.y) * Mi;
    Mn = Mn * Matrice::mat_rotation_y(rotation.y);

    Md = Md * Matrice::mat_rotation_z(rotation.z);
    Mi = Matrice::mat_rotation_z(-rotation.z) * Mi;
    Mn = Mn * Matrice::mat_rotation_z(rotation.z);
}

void Ellipsoide::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Ellipsoide::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Sphere* ellipsoideCanonique = getFormeCanonique();
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!ellipsoideCanonique->intersection(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Vecteur(Mn * normale);
    normale = normale.unitaire();

    return true;
}