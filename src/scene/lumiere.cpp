#include "../../include/scene/lumiere.h"
#include "../../include/geometrie/point.h"

Lumiere::Lumiere() : Lumiere(Point(), 0) {

}

Lumiere::Lumiere(const Lumiere& lumiere) : Lumiere(lumiere.position, lumiere.intensite) {

}

Lumiere::Lumiere(Point position, double intensite) {
    this->position = Point(position);
    this->intensite = intensite;
}

Lumiere::~Lumiere() {

}