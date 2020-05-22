#include "../../include/scene/sphere.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"

Sphere::Sphere(Point centre, double rayon, bool estCanonique) {
    this->centre = Point(centre);
    this->rayon = rayon;
}

Sphere::Sphere(Point centre, double rayon) : Sphere(centre, rayon, false) {

}

Sphere::Sphere(const Sphere& sphere) : Sphere(sphere.centre, sphere.rayon) {

}

Sphere::~Sphere() {

}

Sphere* Sphere::creerFormeCanonique() {
    // Sphère de rayon 1 centré à l'origine.
    return new Sphere(Point(0, 0, 0), 1, true);
}

Sphere* Sphere::getFormeCanonique() {
    return (Sphere*) formeCanonique;
}

Point Sphere::getCentre() {
    return Point(centre);
}

void Sphere::homothetieFormeCanonique() {
    Sphere* sphereCanonique = getFormeCanonique();

    Md = Md * Matrice::mat_homothetie(rayon, rayon, rayon);
    Mi = Mi * Matrice::mat_homothetie(sphereCanonique->rayon / rayon, sphereCanonique->rayon / rayon, sphereCanonique->rayon / rayon);
}

void Sphere::rotationFormeCanonique() {

}

void Sphere::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}