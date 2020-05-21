#include "../../include/scene/triangle.h"
#include "../../include/geometrie/point.h"

Triangle::Triangle(Point a, Point b, Point c, bool estCanonique) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Triangle::Triangle(Point a, Point b, Point c) : Triangle(a, b, c, false) {

}

Triangle::Triangle(const Triangle& tr) : Triangle(tr.a, tr.b, tr.c) {

}

Triangle::~Triangle() {

}

Triangle* Triangle::creerFormeCanonique() {
    // Triangle équilatéral de longueur racine de 5 centré sur l'origine, dans le plan z = 0
    return new Triangle(Point(-1, -1, 0), Point(0, 1, 0), Point(1, -1, 0), true);
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