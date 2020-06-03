#include "../../include/scene/forme.h"
#include "../../include/outils/materiau.h"
#include <vector>

using namespace std;

Forme::Forme() : Forme(Point(), Vecteur(), Materiau()) {

}

Forme::Forme(Point centre, Vecteur rotation, Materiau materiau, bool forme2D) {
    formeCanonique = nullptr;

    this->centre = centre;
    this->rotation = rotation;
    this->materiau = Materiau(materiau);
    this->forme2D = forme2D;
}

Forme::~Forme() {
    delete formeCanonique;
}

void Forme::initialiserMatricesTransformation() {
    formeCanonique = creerFormeCanonique();

    translationFormeCanonique();
    rotationFormeCanonique();
    homothetieFormeCanonique();
}