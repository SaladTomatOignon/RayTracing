#include "../../include/scene/triangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(Point(), rotation, materiau, forme2D = true) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
}

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation) : Triangle(a, b, c, rotation, Materiau(), false) {

}

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation, Materiau materiau) : Triangle(a, b, c, rotation, materiau, false) {

}

Triangle::Triangle(const Triangle& tr) : Triangle(tr.a, tr.b, tr.c, tr.rotation, tr.materiau) {

}

Triangle::~Triangle() {

}

Triangle* Triangle::creerFormeCanonique() {
    // Triangle équilatéral de longueur racine de 5 centré sur l'origine, dans le plan z = 0
    return new Triangle(Point(-1, -1, 0), Point(0, 1, 0), Point(1, -1, 0), Vecteur(), Materiau(), true);
}

Triangle* Triangle::getFormeCanonique() {
    return (Triangle*) formeCanonique;
}

Point Triangle::getCentre() {
    return Point(); // TODO
}

void Triangle::homothetieFormeCanonique() {

}

void Triangle::rotationFormeCanonique() {
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

void Triangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
}

bool Triangle::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    return false;
}