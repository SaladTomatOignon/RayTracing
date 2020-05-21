#include "../../include/scene/camera.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"
#include <stdexcept>

Camera::Camera() : Camera(Point(), Vecteur()) {

}

Camera::Camera(const Camera& camera) : Camera(Point(camera.position), Vecteur(camera.orientation)) {

}

Camera::Camera(Point position, Vecteur orientation) {
    if (orientation != orientation.unitaire()) { /* Si le vecteur donné n'est pas unitaire */
        throw std::invalid_argument("Le vecteur d'orientation de la caméra doit être un vecteur unitaire");
    }

    this->position = Point(position);
    this->orientation = Vecteur(orientation);
}

Camera::~Camera() {

}