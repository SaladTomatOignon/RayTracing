#include "../../include/scene/rectangle.h"
#include "../../include/geometrie/point.h"
#include <iostream>

Rectangle::Rectangle(Point a, Point b, Point c, Point d) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.a, rect.b, rect.c, rect.d) {

}

Rectangle::~Rectangle() {

}