#include "../../include/outils/image.h"
#include "../../include/outils/couleur.h"
#include <fstream>

using namespace std;

Image::Image(unsigned int largeur, unsigned int hauteur) {
    this->largeur = largeur;
    this->hauteur = hauteur;

    this->valeurs = new Couleur* [hauteur];
    for (unsigned int i = 0; i < hauteur; i++) {
        this->valeurs[i] = new Couleur[largeur];
    }
}

Image::Image(const Image& image) : Image(image.largeur, image.hauteur) {
    for (unsigned int i = 0; i < hauteur; i++) {
        for (unsigned int j = 0; j < largeur; j++) {
            this->valeurs[i][j] = Couleur(image.valeurs[i][j]);
        }
    }
}

Image::~Image() {
    for (unsigned int i = 0; i < hauteur; i++) {
        delete [] valeurs[i];
    }

    delete [] valeurs;
}

Couleur* Image::operator[](int const& i) {
    return valeurs[i];
}

Image& Image::operator=(Image const& autre) {
    if (&autre != this) {
        for (unsigned int i = 0; i < hauteur; i++) {
            for (unsigned int j = 0; j < largeur; j++) {
                this->valeurs[i][j] = Couleur(autre.valeurs[i][j]);
            }
        }
    }

    return *this;
}

void Image::exportPPM(const char* fileName) {
    ofstream fichier(fileName);

    fichier << "P3" << endl;
    fichier << largeur << " " << hauteur << endl;
    fichier << "255" << endl;

    for (unsigned int i = 0; i < hauteur; i++) {
        for (unsigned int j = 0; j < largeur; j++) {
            fichier << (int) valeurs[i][j].r << " " << (int) valeurs[i][j].g << " " << (int) valeurs[i][j].b;
            if (j < largeur - 1) {
                fichier << '\t';
            }
        }
        fichier << endl;
    }
}