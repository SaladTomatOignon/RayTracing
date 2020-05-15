#include "../../include/scene/triangle.h"
#include "../../include/geometrie/point.h"
#include <iostream>

Triangle::Triangle(Point a, Point b, Point c) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
}

Triangle::Triangle(const Triangle& tr) {
    this->a = Point(tr.a);
    this->b = Point(tr.b);
    this->c = Point(tr.c);
}

Triangle::~Triangle() {

}

Triangle* Triangle::clone() const {
    return new Triangle(*this);
}