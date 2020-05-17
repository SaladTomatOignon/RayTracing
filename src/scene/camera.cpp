#include "../../include/scene/camera.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"

Camera::Camera() : Camera(Point(), Vecteur()) {

}

Camera::Camera(const Camera& camera) : Camera(Point(camera.position), Vecteur(camera.orientation)) {

}

Camera::Camera(Point position, Vecteur orientation) {
    this->position = Point(position);
    this->orientation = Vecteur(orientation);
}

Camera::~Camera() {

}