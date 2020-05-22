#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"
#include <math.h>

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

Point Point::operator+(const Vecteur& v) {
    return Point(x + v.x, y + v.y, z + v.z);
}

Point Point::operator-(const Vecteur& v) {
    return Point(x - v.x, y - v.y, z - v.z);
}

Point Point::operator-(const Point& p) {
    return Point(x - p.x, y - p.y, z - p.z);
}

Vecteur Point::creerVecteur(Point a, Point b) {
    return Vecteur(b.x - a.x, b.y - a.y, b.z - a.z);
}

double Point::distance(Point a) {
    return sqrt(pow(a.x - x, 2) +
                pow(a.y - y, 2) +
                pow(a.z - z, 2));
}