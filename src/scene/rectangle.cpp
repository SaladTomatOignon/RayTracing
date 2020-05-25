#include "../../include/scene/rectangle.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Couleur couleur, bool estCanonique) : Forme(couleur) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Couleur couleur) : Rectangle(a, b, c, d, couleur, false) {

}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : Rectangle(a, b, c, d, Couleur(), false) {

}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.a, rect.b, rect.c, rect.d, rect.couleur) {

}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::creerFormeCanonique() {
    // Carré de côté 2 centré sur l'origine, dans le plan z = 0
    return new Rectangle(Point(-1, -1, 0), Point(-1, 1, 0), Point(1, 1, 0), Point(1, -1, 0), Couleur(), true);
}

Rectangle* Rectangle::getFormeCanonique() {
    return (Rectangle*) formeCanonique;
}

Point Rectangle::getCentre() {
    return Point(); // TODO
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