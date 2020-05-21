#include "../../include/scene/scene.h"
#include <algorithm>

Scene::Scene() : Scene(Camera(), vector<Forme*>()) {

}

Scene::Scene(Camera camera, vector<Forme*> formes) {
    this->camera = Camera(camera);
    this->formes = vector<Forme*>();

    /* Copie du vector de Forme. */
    for (const auto* forme : formes) {
        this->formes.push_back(forme->clone());
    }
}

Scene::~Scene() {
    formes.clear();
}