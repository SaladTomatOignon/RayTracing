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
    double vitesseDeplacement = 1.5;

    switch (direction) {
        case DIRECTION::GAUCHE:
            position = position - vitesseDeplacement * axeHorizontal;
            break;
        case DIRECTION::HAUT:
            position = position + vitesseDeplacement * axeVertical;
            break;
        case DIRECTION::DROITE:
            position = position + vitesseDeplacement * axeHorizontal;
            break;
        case DIRECTION::BAS:
            position = position - vitesseDeplacement * axeVertical;
            break;
        case DIRECTION::DEVANT:
            position = position + vitesseDeplacement * orientation.unitaire();
            break;
        case DIRECTION::DERRIERE:
            position = position - vitesseDeplacement * orientation.unitaire();
            break;
        default:
            break;
    }
}

void Camera::orienter(DIRECTION direction) {
    Vecteur vecteurHorizontal = Vecteur(1, 0, 0).unitaire();
    Vecteur vecteurVertical = Vecteur(0, 1, 0).unitaire();
    Vecteur axeHorizontal = orientation.prodVectoriel(vecteurVertical);
    Vecteur axeVertical = orientation.prodVectoriel(axeHorizontal);
    double vitesseRotation = M_PI / 48;

    switch (direction) {
    case DIRECTION::GAUCHE:
        orientation = (Matrice::mat_rotation_axe(axeVertical, vitesseRotation) * orientation).unitaire();
        break;
    case DIRECTION::HAUT:
        orientation = (Matrice::mat_rotation_axe(axeHorizontal, vitesseRotation) * orientation).unitaire();
        break;
    case DIRECTION::DROITE:
        orientation = (Matrice::mat_rotation_axe(axeVertical, -vitesseRotation) * orientation).unitaire();
        break;
    case DIRECTION::BAS:
        orientation = (Matrice::mat_rotation_axe(axeHorizontal, -vitesseRotation) * orientation).unitaire();
        break;
    default:
        break;
    }
}