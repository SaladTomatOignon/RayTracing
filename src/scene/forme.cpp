#include "../../include/scene/forme.h"
#include "../../include/outils/materiau.h"

Forme::Forme() : Forme(Materiau()) {

}

Forme::Forme(Materiau materiau) {
    formeCanonique = nullptr;

    this->materiau = Materiau(materiau);
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