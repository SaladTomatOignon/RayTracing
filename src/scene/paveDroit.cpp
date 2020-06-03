#define _USE_MATH_DEFINES

#include "../../include/scene/paveDroit.h"
#include "../../include/scene/cube.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>
#include <iostream>

PaveDroit::PaveDroit(Point centre, double largeur, double hauteur, double profondeur, Vecteur rotation, Materiau materiau) : Forme(centre, rotation, materiau) {
    this->largeur = largeur;
    this->hauteur = hauteur;
    this->profondeur = profondeur;

    initialiserMatricesTransformation();
}

PaveDroit::PaveDroit(Point centre, double largeur, double hauteur, double profondeur, Vecteur rotation) : PaveDroit(centre, largeur, hauteur, profondeur, rotation, Materiau()) {

}

PaveDroit::PaveDroit(const PaveDroit& paveDroit) : PaveDroit(paveDroit.centre, paveDroit.largeur, paveDroit.hauteur, paveDroit.profondeur, paveDroit.rotation, paveDroit.materiau) {
}

PaveDroit::~PaveDroit() {

}

Cube* PaveDroit::creerFormeCanonique() {
    // Cube centré en (0, 0, 0) de longueur 2
    return new Cube(Point(0, 0, 0), 2, Vecteur(0, 0, 0), Materiau(), true);
}

Cube* PaveDroit::getFormeCanonique() {
    return (Cube*) formeCanonique;
}

Point PaveDroit::getCentre() {
    return Point(centre);
}

void PaveDroit::homothetieFormeCanonique() {
    Cube* cubeCanonique = getFormeCanonique();

    Md = Md * Matrice::mat_homothetie(largeur / cubeCanonique->taille, hauteur / cubeCanonique->taille, profondeur / cubeCanonique->taille);
    Mi = Matrice::mat_homothetie(1 / (largeur / cubeCanonique->taille), 1 / (hauteur / cubeCanonique->taille), 1 / (profondeur / cubeCanonique->taille)) * Mi;
    Mn = Mn * Matrice::mat_homothetie((hauteur / cubeCanonique->taille) * (profondeur / cubeCanonique->taille), (largeur / cubeCanonique->taille) * (profondeur / cubeCanonique->taille), (largeur / cubeCanonique->taille) * (hauteur / cubeCanonique->taille));
}

void PaveDroit::rotationFormeCanonique() {
    Md = Md * Matrice::mat_rotation_x(rotation.x);
    Mi = Matrice::mat_rotation_x(-rotation.x) * Mi;
    Mn = Mn * Matrice::mat_rotation_x(rotation.x);

    Md = Md * Matrice::mat_rotation_y(rotation.y);
    Mi = Matrice::mat_rotation_y(-rotation.y) * Mi;
    Mn = Mn * Matrice::mat_rotation_y(rotation.y);

    Md = Md * Matrice::mat_rotation_z(rotation.z);
    Mi = Matrice::mat_rotation_z(-rotation.z) * Mi;
    Mn = Mn * Matrice::mat_rotation_z(rotation.z);
}

void PaveDroit::translationFormeCanonique() {
    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool PaveDroit::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Cube* cubeCanonique = getFormeCanonique();
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!cubeCanonique->intersection(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}