#include "../../include/scene/sphere.h"
#include "../../include/geometrie/point.h"

Sphere::Sphere(Point centre, double rayon, bool estCanonique) {
    this->centre = Point(centre);
    this->rayon = rayon;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
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

void Sphere::homothetieFormeCanonique() {

}

void Sphere::rotationFormeCanonique() {

}

void Sphere::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}