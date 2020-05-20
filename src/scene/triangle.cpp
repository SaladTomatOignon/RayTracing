#include "../../include/scene/triangle.h"
#include "../../include/geometrie/point.h"
#include <iostream>

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
    // Triangle �quilat�ral de longueur racine de 5 centr� sur l'origine, dans le plan z = 0
    return new Triangle(Point(-1, -1, 0), Point(0, 1, 0), Point(1, -1, 0), true);
}

void Triangle::homothetieFormeCanonique() {

}

void Triangle::rotationFormeCanonique() {

}

void Triangle::translationFormeCanonique() {

}