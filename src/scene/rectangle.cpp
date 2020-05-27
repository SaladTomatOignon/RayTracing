#include "../../include/scene/rectangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Materiau materiau, bool estCanonique) : Forme(materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Materiau materiau) : Rectangle(a, b, c, d, materiau, false) {

}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : Rectangle(a, b, c, d, Materiau(), false) {

}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.a, rect.b, rect.c, rect.d, rect.materiau) {

}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::creerFormeCanonique() {
    // Carr� de c�t� 2 centr� sur l'origine, dans le plan z = 0
    return new Rectangle(Point(-1, -1, 0), Point(-1, 1, 0), Point(1, 1, 0), Point(1, -1, 0), Materiau(), true);
}

Rectangle* Rectangle::getFormeCanonique() {
    return (Rectangle*) formeCanonique;
}

Point Rectangle::getCentre() {
    return Point(
        (a.x + b.x + c.x + d.x) / 4,
        (a.y + b.y + c.y + d.y) / 4,
        (a.z + b.z + c.z + d.z) / 4
    );
}

void Rectangle::homothetieFormeCanonique() {

}

void Rectangle::rotationFormeCanonique() {

}

void Rectangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}

bool Rectangle::intersection(Rayon r, Point& intersection, Vecteur& normale) {
    return false;
}