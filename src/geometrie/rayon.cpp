#include "../../include/geometrie/rayon.h"

Rayon::Rayon() : Rayon(Point(), Vecteur()) {

}

Rayon::Rayon(Point o, Vecteur u) {
    this->origine = o;
    this->direction = u;
}

Rayon::Rayon(const Rayon& rayon) : Rayon(rayon.origine, rayon.direction) {
    
}

Rayon::~Rayon() {

}