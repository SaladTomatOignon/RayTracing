#include "../../include/scene/triangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Triangle::Triangle(Point a, Point b, Point c, Materiau materiau, bool estCanonique) : Forme(materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
}

Triangle::Triangle(Point a, Point b, Point c) : Triangle(a, b, c, Materiau(), false) {

}

Triangle::Triangle(Point a, Point b, Point c, Materiau materiau) : Triangle(a, b, c, materiau, false) {

}

Triangle::Triangle(const Triangle& tr) : Triangle(tr.a, tr.b, tr.c, tr.materiau) {

}

Triangle::~Triangle() {

}

Triangle* Triangle::creerFormeCanonique() {
    // Triangle équilatéral de longueur racine de 5 centré sur l'origine, dans le plan z = 0
    return new Triangle(Point(-1, -1, 0), Point(0, 1, 0), Point(1, -1, 0), Materiau(), true);
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

}

void Triangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}

bool Triangle::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    return false;
}