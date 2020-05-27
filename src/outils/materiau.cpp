#include "../../include/outils/materiau.h"
#include "../../include/outils/couleur.h"

Materiau::Materiau() : Materiau(Couleur(), 0, Couleur()) {

}

Materiau::Materiau(const Materiau& materiau) : Materiau(materiau.couleur, materiau.brillance, materiau.specularite) {

}

Materiau::Materiau(Couleur couleur, int brillance, Couleur specularite) {
    this->couleur = Couleur(couleur);
    this->brillance = brillance;
    this->specularite = Couleur(specularite);
}

Materiau::~Materiau() {

}