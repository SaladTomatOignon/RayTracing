#include "../../include/scene/sphere.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>

Sphere::Sphere(Point centre, double rayon, Materiau materiau, bool estCanonique) : Forme(materiau) {
    this->centre = Point(centre);
    this->rayon = rayon;
}

Sphere::Sphere(Point centre, double rayon, Materiau materiau) : Sphere(centre, rayon, materiau, false) {

}

Sphere::Sphere(Point centre, double rayon) : Sphere(centre, rayon, Materiau(), false) {

}

Sphere::Sphere(const Sphere& sphere) : Sphere(sphere.centre, sphere.rayon, sphere.materiau) {

}

Sphere::~Sphere() {

}

Sphere* Sphere::creerFormeCanonique() {
    // Sph�re de rayon 1 centr� � l'origine.
    return new Sphere(Point(0, 0, 0), 1, Materiau(), true);
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

bool Sphere::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Vecteur u = r.direction.unitaire();

    Point L = centre - r.origine;
    Vecteur vL = Vecteur(L.x, L.y, L.z);
    double d = vL.prodScalaire(u);
    double l2 = vL.prodScalaire(vL);

    if (d < 0 && l2 > rayon * rayon) {
        return false;
    }

    double m2 = l2 - d * d;

    if (m2 > rayon * rayon) {
        return false;
    }

    double q = sqrt(rayon * rayon - m2);

    double t;
    if (l2 > rayon * rayon) {
        t = d - q;
    } else {
        t = d + q;
    }

    intersection = Point(r.origine + t * u);
    normale = (1 / rayon) * Point::creerVecteur(centre, intersection);

    return true;
}