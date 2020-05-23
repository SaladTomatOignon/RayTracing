#include "../../include/outils/couleur.h"

Couleur::Couleur() : Couleur(0, 0, 0) {

}

Couleur::Couleur(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Couleur::Couleur(const Couleur& couleur) : Couleur(couleur.r, couleur.g, couleur.b) {

}

Couleur::~Couleur() {

}