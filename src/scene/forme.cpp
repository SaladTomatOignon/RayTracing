#include "../../include/scene/forme.h"
#include "../../include/outils/couleur.h"

Forme::Forme() : Forme(Couleur()) {

}

Forme::Forme(Couleur couleur) {
    formeCanonique = nullptr;

    this->couleur = couleur;
}

Forme::~Forme() {
    delete formeCanonique;
}

void Forme::initialiserMatricesTransformation() {
    formeCanonique = creerFormeCanonique();

    homothetieFormeCanonique();
    rotationFormeCanonique();
    translationFormeCanonique();
}