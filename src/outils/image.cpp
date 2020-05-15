#include "../../include/outils/image.h"
#include "../../include/scene/pixel.h"
#include <iostream>
#include <fstream>

using namespace std;

Image::Image(unsigned int largeur, unsigned int hauteur) {
    this->largeur = largeur;
    this->hauteur = hauteur;

    this->valeurs = new Pixel* [hauteur];
    for (int i = 0; i < hauteur; i++) {
        this->valeurs[i] = new Pixel[largeur];
    }
}

Image::Image(const Image& image) : Image(image.largeur, image.hauteur) {

}

Image::~Image() {
    for (int i = 0; i < hauteur; i++) {
        delete [] valeurs[i];
    }

    delete [] valeurs;
}

Pixel* Image::operator[](int const& i) {
    return valeurs[i];
}


void Image::exportPPM(const char* fileName) {
    ofstream fichier(fileName);

    fichier << "P3" << endl;
    fichier << largeur << " " << hauteur << endl;
    fichier << "255" << endl;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fichier << valeurs[i][j].r << " " << valeurs[i][j].g << " " << valeurs[i][j].b;
            if (j < largeur - 1) {
                fichier << "\t";
            }
        }
        fichier << endl;
    }
}