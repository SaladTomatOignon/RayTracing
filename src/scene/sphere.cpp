#include "../../include/scene/sphere.h"
#include "../../include/geometrie/point.h"
#include <iostream>

Sphere::Sphere(Point centre, double rayon) {
    this->centre = Point(centre);
    this->rayon = rayon;
}

Sphere::Sphere(const Sphere& sphere) : Sphere(sphere.centre, sphere.rayon) {

}

Sphere::~Sphere() {

}