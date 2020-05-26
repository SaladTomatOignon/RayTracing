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

Couleur Couleur::operator*(const double& reel) {
    return Couleur(r*reel, g*reel, b*reel);
}

Couleur Couleur::operator+(const Couleur& autre) {
    return Couleur(r + autre.r, g + autre.g, b + autre.b);
}