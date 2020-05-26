#include "../../include/outils/materiau.h"
#include "../../include/outils/couleur.h"

Materiau::Materiau() : Materiau(Couleur(), 0) {

}

Materiau::Materiau(const Materiau& materiau) : Materiau(materiau.couleur, materiau.brillance) {

}

Materiau::Materiau(Couleur couleur, int brillance) {
    this->couleur = Couleur(couleur);
    this->brillance = brillance;
}

Materiau::~Materiau() {

}