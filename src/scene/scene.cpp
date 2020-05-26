#include "../../include/scene/scene.h"
#include "../../include/scene/lumiere.h"

Scene::Scene() : Scene(Camera(), Grille(), vector<Forme*>(), vector<Lumiere>()) {

}

Scene::Scene(Camera camera, Grille grille, vector<Forme*> formes, vector<Lumiere> lumieres) {
    this->camera = Camera(camera);
    this->formes = vector<Forme*>();
    this->lumieres = vector<Lumiere>();
    this->grille = Grille(grille);

    this->grille.positionner(this->camera);

    /* Copie du vector de Forme. */
    for (const auto* forme : formes) {
        this->formes.push_back(forme->clone());
    }

    /* Copie du vector de Lumiere. */
    for (const auto lumiere : lumieres) {
        this->lumieres.push_back(lumiere);
    }
}

Scene::Scene(const Scene& scene) : Scene(scene.camera, scene.grille, scene.formes, scene.lumieres) {

}

Scene::~Scene() {
    formes.clear();
    lumieres.clear();
}