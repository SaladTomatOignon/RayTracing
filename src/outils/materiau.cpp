#include "../../include/outils/materiau.h"
#include "../../include/outils/couleur.h"

Materiau::Materiau() : Materiau(Couleur(), 0, Couleur(), 0) {

}

Materiau::Materiau(const Materiau& materiau) : Materiau(materiau.couleur, materiau.brillance, materiau.specularite, materiau.reflexion) {

}

Materiau::Materiau(Couleur couleur, int brillance, Couleur specularite, float reflexion) {
    this->couleur = Couleur(couleur);
    this->brillance = brillance;
    this->specularite = Couleur(specularite);
    this->reflexion = reflexion;
}

Materiau::~Materiau() {

}