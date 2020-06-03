#include "../../include/scene/rectangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(Point(), rotation, materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Vecteur rotation, Materiau materiau) : Rectangle(a, b, c, d, rotation, materiau, false) {

}

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Vecteur rotation) : Rectangle(a, b, c, d, rotation, Materiau(), false) {

}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.a, rect.b, rect.c, rect.d, rect.rotation, rect.materiau) {

}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::creerFormeCanonique() {
    // Carré de côté 2 centré sur l'origine, dans le plan z = 0
    return new Rectangle(Point(-1, -1, 0), Point(-1, 1, 0), Point(1, 1, 0), Point(1, -1, 0), Vecteur(), Materiau(), true);
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

void Rectangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
}

bool Rectangle::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    return false;
}