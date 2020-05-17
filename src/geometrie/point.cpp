#include "../../include/geometrie/point.h"

Point::Point() : Point(0, 0, 0) {

}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Point& point) : Point(point.x, point.y, point.z) {

}

Point::~Point() {

}