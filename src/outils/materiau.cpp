#include "../../include/outils/materiau.h"
#include "../../include/outils/couleur.h"

Materiau::Materiau() : Materiau(Couleur(), 0, Couleur(), 0, 0, 1) {

}

Materiau::Materiau(const Materiau& materiau) : Materiau(materiau.couleur, materiau.brillance, materiau.specularite, materiau.reflexion, materiau.coeffRefraction, materiau.indiceRefraction) {

}

Materiau::Materiau(Couleur couleur, int brillance, Couleur specularite, float reflexion, float coeffRefraction, float indiceRefraction) {
    this->couleur = Couleur(couleur);
    this->brillance = brillance;
    this->specularite = Couleur(specularite);
    this->reflexion = reflexion;
    this->coeffRefraction = coeffRefraction;
    this->indiceRefraction = indiceRefraction;
}

Materiau::~Materiau() {

}