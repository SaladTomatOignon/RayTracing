#include "../../include/geometrie/vecteur.h"

Vecteur::Vecteur() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vecteur::Vecteur(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vecteur::Vecteur(const Vecteur& vecteur) : Vecteur(vecteur.x, vecteur.y, vecteur.z) {

}

Vecteur::~Vecteur() {

}