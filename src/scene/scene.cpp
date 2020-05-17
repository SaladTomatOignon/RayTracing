#include "../../include/scene/scene.h"
#include <algorithm>

Scene::Scene() : Scene(Camera(), vector<Forme*>()) {

}

Scene::Scene(Camera camera, vector<Forme*> formes) {
    this->camera = Camera(camera);
    this->formes = vector<Forme*>(formes.size());
    transform(formes.begin(), formes.end(), this->formes.begin(), [](Forme* s) -> Forme* { return s->clone(); }); /* Copie du vector de Forme. */
}

Scene::~Scene() {

}