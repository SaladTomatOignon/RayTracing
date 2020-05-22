#include "../../include/geometrie/rayon.h"

Rayon::Rayon() : Rayon(Point(), Vecteur()) {

}

Rayon::Rayon(Point o, Vecteur u) {
    this->origine = Point(o);
    this->direction = Vecteur(u);
}

Rayon::Rayon(const Rayon& rayon) : Rayon(Point(rayon.origine), Vecteur(rayon.direction)) {
    
}

Rayon::~Rayon() {

}