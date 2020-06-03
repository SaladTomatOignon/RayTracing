#include "../../include/scene/cylindre.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(Point(), rotation, materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->rayon = rayon;
}

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation, Materiau materiau) : Cylindre(a, b, rayon, rotation, materiau, false) {

}

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation) : Cylindre(a, b, rayon, rotation, Materiau(), false) {

}

Cylindre::Cylindre(const Cylindre& cylindre) : Cylindre(cylindre.a, cylindre.b, cylindre.rayon, cylindre.rotation, cylindre.materiau) {

}

Cylindre::~Cylindre() {

}

Cylindre* Cylindre::creerFormeCanonique() {
    /* Cylindre centré à l'origine de rayon 1 et de hauteur 2 */
    return new Cylindre(
        Point(0, -1, 0),
        Point(0, 1, 0),
        1,
        Vecteur(0, 0, 0)
    );
}

Cylindre* Cylindre::getFormeCanonique() {
    return (Cylindre*) formeCanonique;
}

Point Cylindre::getCentre() {
    return Point(
        (a.x + b.x) / 2,
        (a.y + b.y) / 2,
        (a.z + b.z) / 2
    );
}

void Cylindre::homothetieFormeCanonique() {

}

void Cylindre::rotationFormeCanonique() {
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

void Cylindre::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
}

bool Cylindre::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    return false; // TODO
}