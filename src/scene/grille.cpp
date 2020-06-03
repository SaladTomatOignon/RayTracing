#include "../../include/scene/grille.h"
#include "../../include/scene/rectangle.h"
#include "../../include/scene/camera.h"
#include <stdexcept>

Grille::Grille() : Grille(0, 0, 0, 0, 0, Vecteur()) {
    
}

Grille::Grille(double largeur, double hauteur, unsigned int resolution_l, unsigned int resolution_h, double distance_focale, Vecteur inclinaison) {
    Vecteur vecteurNul = inclinaison - inclinaison.unitaire();

    if (abs(Vecteur::sommeCoeff(vecteurNul)) > _ZERO_) {
        throw std::invalid_argument("Le vecteur d'inclinaison de la grille doit �tre un vecteur unitaire");
    }

    this->largeur = largeur;
    this->hauteur = hauteur;
    this->resolution_l = resolution_l;
    this->resolution_h = resolution_h;
    this->distance_focale = distance_focale;
    this->inclinaison_h = Vecteur(inclinaison);
}

Grille::Grille(const Grille& grille) : Grille(grille.largeur, grille.hauteur, grille.resolution_l, grille.resolution_h, grille.distance_focale, Vecteur(grille.inclinaison_h)) {
    this->inclinaison_v = grille.inclinaison_v;
    this->position = grille.position;
    this->estPositionne = grille.estPositionne;
}

Grille::~Grille() {

}

void Grille::positionner(Camera camera) {
    /* On suppose que la cam�ra est au mileu de la grille � une distance `distance_focale` en z. */
    inclinaison_v = -1 * inclinaison_h.prodVectoriel(camera.orientation).unitaire();
    /* a = Position de la cam�ra. b = Position du point qu'on cherche (le point en haut � gauche de la grille) */
    Vecteur ab = distance_focale * camera.orientation - (largeur / 2) * inclinaison_h + (hauteur / 2) * inclinaison_v;

    position = camera.position + ab;
    estPositionne = true;
}

Rectangle Grille::at(unsigned int i, unsigned int j) {
    if (!estPositionne) {
        throw std::logic_error("La grille doit d'abord �tre positionn�e avant d'acc�der � ses coordonn�es");
    }

    if (i < 0 || i > resolution_h - 1 || j < 0 || j > resolution_l - 1) {
        throw std::out_of_range("Indice(s) invalide(s)");
    }

    double tailleCaseLargeur = largeur / resolution_l;
    double tailleCaseHauteur = hauteur / resolution_h;

    Point A = position - (i + 1.0) * tailleCaseHauteur * inclinaison_v + (j + 1.0) * tailleCaseLargeur * inclinaison_h;

    return Rectangle(
        Point(A), /* Point haut gauche */
        Point(A + tailleCaseHauteur * inclinaison_v), /* Point bas gauche */
        Point(A + tailleCaseHauteur * inclinaison_v + tailleCaseLargeur * inclinaison_h), /* Point bas droit */
        Point(A + tailleCaseLargeur * inclinaison_h), /* Point haut droit */
        Vecteur()
    );
}

Vecteur Grille::centrePixel(unsigned int i, unsigned int j) {
    return  - (largeur / 2) * inclinaison_h + (hauteur / 2) * inclinaison_v // Point haut gauche de la grille
            + (j + 1.0 / 2.0) * (largeur / resolution_l) * inclinaison_h  // Decalage horizontal
            - (i + 1.0 / 2.0) * (hauteur / resolution_h) * inclinaison_v; // Decalage vertical
}

Vecteur Grille::pointAleatoirePixel(unsigned int i, unsigned int j) {
    return  - (largeur / 2) * inclinaison_h + (hauteur / 2) * inclinaison_v // Point haut gauche de la grille
            + (j + (((double)rand() / (RAND_MAX)) + 1)) * (largeur / resolution_l) * inclinaison_h  // Decalage horizontal
            - (i + (((double)rand() / (RAND_MAX)) + 1)) * (hauteur / resolution_h) * inclinaison_v; // Decalage vertical
}