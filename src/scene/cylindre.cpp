#include "../../include/scene/cylindre.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Cylindre::Cylindre(Point a, Point b, double rayon, Materiau materiau, bool estCanonique) : Forme(materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->rayon = rayon;
}

Cylindre::Cylindre(Point a, Point b, double rayon, Materiau materiau) : Cylindre(a, b, rayon, materiau, false) {

}

Cylindre::Cylindre(Point a, Point b, double rayon) : Cylindre(a, b, rayon, Materiau(), false) {

}

Cylindre::Cylindre(const Cylindre& cylindre) : Cylindre(cylindre.a, cylindre.b, cylindre.rayon, cylindre.materiau) {

}

Cylindre::~Cylindre() {

}

Cylindre* Cylindre::creerFormeCanonique() {
    /* Cylindre centr� � l'origine de rayon 1 et de hauteur 2 */
    return new Cylindre(
        Point(0, -1, 0),
        Point(0, 1, 0),
        1
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

}

void Cylindre::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}

bool Cylindre::intersection(Rayon r, Point& intersection, Vecteur& normale) {
    return false; // TODO
}