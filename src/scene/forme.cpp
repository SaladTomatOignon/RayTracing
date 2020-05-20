#include "../../include/scene/forme.h"
#include <iostream>

Forme::Forme() {
    formeCanonique = nullptr;
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