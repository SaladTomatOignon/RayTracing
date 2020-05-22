#include "../../include/scene/rectangle.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"

Rectangle::Rectangle(Point a, Point b, Point c, Point d, bool estCanonique) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(Point a, Point b, Point c, Point d) : Rectangle(a, b, c, d, false) {

}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.a, rect.b, rect.c, rect.d) {

}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::creerFormeCanonique() {
    // Carr� de c�t� 2 centr� sur l'origine, dans le plan z = 0
    return new Rectangle(Point(-1, -1, 0), Point(-1, 1, 0), Point(1, 1, 0), Point(1, -1, 0), true);
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