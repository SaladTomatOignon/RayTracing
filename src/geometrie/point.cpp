#include "../../include/geometrie/point.h"

Point::Point() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(const Point& point) {
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

Point::~Point() {

}