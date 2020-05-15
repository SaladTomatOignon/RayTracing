#include "../../include/scene/rectangle.h"
#include "../../include/geometrie/point.h"
#include <iostream>

Rectangle::Rectangle(Point a, Point b, Point c, Point d) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);
    this->d = Point(d);
}

Rectangle::Rectangle(const Rectangle& rect) {
    this->a = Point(rect.a);
    this->b = Point(rect.b);
    this->c = Point(rect.c);
    this->d = Point(rect.d);
}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
}