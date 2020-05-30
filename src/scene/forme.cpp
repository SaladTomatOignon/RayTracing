#include "../../include/scene/forme.h"
#include "../../include/outils/materiau.h"

Forme::Forme() : Forme(Materiau()) {

}

Forme::Forme(Materiau materiau, bool forme2D) {
    formeCanonique = nullptr;

    this->materiau = Materiau(materiau);
    this->forme2D = forme2D;
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