#include "../../include/scene/sphere.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>

Sphere::Sphere(Point centre, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau) {
    this->rayon = rayon;
}

Sphere::Sphere(Point centre, double rayon, Vecteur rotation, Materiau materiau) : Sphere(centre, rayon, rotation, materiau, false) {

}

Sphere::Sphere(Point centre, double rayon, Vecteur rotation) : Sphere(centre, rayon, rotation, Materiau(), false) {

}

Sphere::Sphere(const Sphere& sphere) : Sphere(sphere.centre, sphere.rayon, sphere.rotation, sphere.materiau) {

}

Sphere::~Sphere() {

}

Sphere* Sphere::creerFormeCanonique() {
    // Sph�re de rayon 1 centr� � l'origine.
    return new Sphere(Point(0, 0, 0), 1, Vecteur(), Materiau(), true);
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
    Mi = Matrice::mat_homothetie(sphereCanonique->rayon / rayon, sphereCanonique->rayon / rayon, sphereCanonique->rayon / rayon) * Mi;
}

void Sphere::rotationFormeCanonique() {
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

void Sphere::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
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