#include "../../include/geometrie/vecteur.h"
#include <math.h>

Vecteur::Vecteur() : Vecteur(0, 0, 0) {

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

bool Vecteur::operator==(const Vecteur& autre) {
    return x == autre.x &&
           y == autre.y &&
           z == autre.z;
}

bool Vecteur::operator!=(const Vecteur& autre) {
    return x != autre.x ||
           y != autre.y ||
           z != autre.z;
}

Vecteur Vecteur::operator+(const Vecteur& autre) {
    return Vecteur(x + autre.x, y + autre.y, z + autre.z);
}

Vecteur Vecteur::operator-(const Vecteur& autre) {
    return Vecteur(x - autre.x, y - autre.y, z - autre.z);
}

Vecteur operator*(const double scalaire, const Vecteur& u) {
    return Vecteur(scalaire * u.x, scalaire * u.y, scalaire * u.z);
}

Vecteur Vecteur::operator/(double reel) {
    return Vecteur(x / reel, y / reel, z / reel);
}

double Vecteur::prodScalaire(Vecteur& v) {
    return x * v.x + y * v.y + z * v.z;
}

Vecteur Vecteur::prodVectoriel(Vecteur& v) {
    return Vecteur(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

Vecteur Vecteur::rotationAxe(Vecteur& axe, double theta) {
    double c = cos(theta);
    double s = sin(theta);

    return c * (*this) + (1 - c) * prodScalaire(axe) * axe + s * axe.prodVectoriel((*this));
}

Vecteur Vecteur::unitaire() {
    if (x == 0 &&
        y == 0 &&
        z == 0) {

        return Vecteur();
    }

    return Vecteur(x / sqrt(prodScalaire(*this)),
                   y / sqrt(prodScalaire(*this)),
                   z / sqrt(prodScalaire(*this))
                  );
}

double Vecteur::sommeCoeff(Vecteur& vecteur) {
    return vecteur.x + vecteur.y + vecteur.z;
}

double Vecteur::normeCarre() {
    return x * x + y * y + z * z;
}