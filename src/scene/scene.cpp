#include "../../include/scene/scene.h"
#include <algorithm>

Scene::Scene() : Scene(Camera(), Grille(), vector<Forme*>()) {

}

Scene::Scene(Camera camera, Grille grille, vector<Forme*> formes) {
    this->camera = Camera(camera);
    this->formes = vector<Forme*>();
    this->grille = Grille(grille);

    this->grille.positionner(this->camera);

    /* Copie du vector de Forme. */
    for (const auto* forme : formes) {
        this->formes.push_back(forme->clone());
    }
}

Scene::~Scene() {
    formes.clear();
}