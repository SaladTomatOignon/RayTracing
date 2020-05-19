#include "../../include/scene/triangle.h"
#include "../../include/geometrie/point.h"
#include <iostream>

Triangle::Triangle(Point a, Point b, Point c) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
}

Triangle::Triangle(const Triangle& tr) : Triangle(tr.a, tr.b, tr.c) {

}

Triangle::~Triangle() {

}