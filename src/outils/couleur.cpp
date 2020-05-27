#include "../../include/outils/couleur.h"
#include <algorithm>

using namespace std;

Couleur::Couleur() : Couleur(0, 0, 0) {

}

Couleur::Couleur(unsigned int r, unsigned int g, unsigned int b) {
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

Couleur Couleur::operator/(const double& reel) {
    return Couleur(r / reel, g / reel, b / reel);
}

Couleur Couleur::clamp() {
    int rClamp = min((int)r, 255);
    int gClamp = min((int)g, 255);
    int bClamp = min((int)b, 255);

    return Couleur(rClamp, gClamp, bClamp);
}