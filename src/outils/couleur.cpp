#include "../../include/outils/couleur.h"
#include <algorithm>

using namespace std;

Couleur::Couleur() : Couleur(0, 0, 0) {

}

Couleur::Couleur(float r, float g, float b) {
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
    float rClamp = min(r, 1.0f);
    float gClamp = min(g, 1.0f);
    float bClamp = min(b, 1.0f);

    return Couleur(rClamp, gClamp, bClamp);
}