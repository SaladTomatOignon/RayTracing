#include "../../include/outils/image.h"
#include "../../include/outils/couleur.h"
#include <fstream>

using namespace std;

Image::Image(unsigned int largeur, unsigned int hauteur) {
    this->largeur = largeur;
    this->hauteur = hauteur;

    this->valeurs = new m_Couleur[hauteur * largeur];
}

Image::Image(const Image& image) : Image(image.largeur, image.hauteur) {
    for (unsigned int i = 0; i < hauteur * largeur; i++) {
        this->valeurs[i] = image.valeurs[i];
    }
}

Image::~Image() {
    delete [] valeurs;
}

Couleur Image::get(unsigned i, unsigned j) {
    m_Couleur couleur = *(valeurs + ((hauteur - 1 - i) * largeur) + j);
    return Couleur(couleur.r , couleur.g , couleur.b );
}

Image::m_Couleur* Image::getData() {
    return valeurs;
}

void Image::set(unsigned i, unsigned j, Couleur& couleur) {
    *(valeurs + ((hauteur - 1 - i) * largeur) + j) = m_Couleur{couleur.r , couleur.g , couleur.b  };
}

Image& Image::operator=(Image const& autre) {
    if (&autre != this) {
        for (unsigned int i = 0; i < hauteur * largeur; i++) {
            this->valeurs[i] = autre.valeurs[i];
        }
    }

    return *this;
}

void Image::exportPPM(string fileName) {
    ofstream fichier(fileName);

    fichier << "P3" << endl;
    fichier << largeur << " " << hauteur << endl;
    fichier << "255" << endl;

    for (unsigned int i = 0; i < hauteur; i++) {
        for (unsigned int j = 0; j < largeur; j++) {
            fichier << (int) (get(i, j).r * 255.0) << " " << (int) (get(i, j).g * 255.0) << " " << (int) (get(i, j).b * 255.0);
            if (j < largeur - 1) {
                fichier << '\t';
            }
        }
        fichier << endl;
    }
}