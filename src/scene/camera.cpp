#define _USE_MATH_DEFINES

#include "../../include/scene/camera.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/vecteur.h"
#include "../../include/geometrie/matrice.h"
#include <stdexcept>
#include <math.h>

Camera::Camera() : Camera(Point(), Vecteur()) {

}

Camera::Camera(const Camera& camera) : Camera(Point(camera.position), Vecteur(camera.orientation)) {

}

Camera::Camera(Point position, Vecteur orientation) {
    Vecteur vecteurNul = orientation - orientation.unitaire();

    if (abs(Vecteur::sommeCoeff(vecteurNul)) > _ZERO_) {
        throw std::invalid_argument("Le vecteur d'orientation de la cam�ra doit �tre un vecteur unitaire");
    }

    this->position = Point(position);
    this->orientation = Vecteur(orientation);
}

Camera::~Camera() {

}

void Camera::translater(DIRECTION direction) {
    Vecteur vecteurHorizontal = Vecteur(0, 1, 0).unitaire();
    Vecteur vecteurVertical = Vecteur(1, 0, 0).unitaire();
    Vecteur axeHorizontal = - 1 * orientation.prodVectoriel(vecteurHorizontal).unitaire();
    Vecteur axeVertical = orientation.prodVectoriel(axeHorizontal).unitaire();

    switch (direction) {
        case DIRECTION::GAUCHE:
            position = position - axeHorizontal;
            break;
        case DIRECTION::HAUT:
            position = position + axeVertical;
            break;
        case DIRECTION::DROITE:
            position = position + axeHorizontal;
            break;
        case DIRECTION::BAS:
            position = position - axeVertical;
            break;
        case DIRECTION::DEVANT:
            position = position + orientation.unitaire();
            break;
        case DIRECTION::DERRIERE:
            position = position - orientation.unitaire();
            break;
        default:
            break;
    }
}

void Camera::orienter(DIRECTION direction) {
    switch (direction) {
        case DIRECTION::GAUCHE:
            orientation = Matrice::mat_rotation_y(-M_PI/64) * orientation;
            break;
        case DIRECTION::HAUT:
            orientation = Matrice::mat_rotation_x(-M_PI / 64) * orientation;
            break;
        case DIRECTION::DROITE:
            orientation = Matrice::mat_rotation_y(M_PI / 64) * orientation;
            break;
        case DIRECTION::BAS:
            orientation = Matrice::mat_rotation_x(M_PI / 64) * orientation;
            break;
        default:
            break;
    }
}