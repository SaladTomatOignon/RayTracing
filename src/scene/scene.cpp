#include "../../include/scene/scene.h"
#include <algorithm>

Scene::Scene() : Scene(Camera(), vector<Forme*>()) {

}

Scene::Scene(Camera camera, vector<Forme*> formes) {
    this->camera = Camera(camera);
    this->formes = vector<Forme*>();

    /* Copie du vector de Forme. */
    for each (Forme* forme in formes) {
        Forme* test = forme->clone();
        this->formes.push_back(test);
    }
}

Scene::~Scene() {
    formes.clear();
}