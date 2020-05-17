#include "../../include/geometrie/matrice.h"
#include <math.h>
#include <stdexcept>

Matrice::Matrice(unsigned int nb_lignes, unsigned int nb_colonnes) {
    this->lignes = nb_lignes;
    this->colonnes = nb_colonnes;

    this->mat = new double* [nb_lignes]();
    for (unsigned int i = 0; i < nb_lignes; i++) {
        this->mat[i] = new double[nb_colonnes]();
    }
}

Matrice::Matrice(const Matrice& matrice) : Matrice(matrice.lignes, matrice.colonnes) {
    for (unsigned int i = 0; i < matrice.lignes; i++) {
        for (unsigned int j = 0; j < matrice.colonnes; j++) {
            this->mat[i][j] = matrice.mat[i][j];
        }
    }
}

Matrice::~Matrice() {
    for (unsigned int i = 0; i < lignes; i++) {
        delete[] mat[i];
    }

    delete[] mat;
}

double* Matrice::operator[](int const& i) {
    return mat[i];
}

Matrice Matrice::operator*(Matrice matrice) {
    Matrice resultat(lignes, colonnes);

    if (this->colonnes != matrice.lignes) {
        throw std::domain_error::domain_error("Matrices incompatibles pour la multiplication");
    }

    for (unsigned int i = 0; i < lignes; i++) {
        for (unsigned int j = 0; j < colonnes; j++) {
            resultat[i][j] = 0;

            for (unsigned int k = 0; k < colonnes; k++) {
                resultat[i][j] += mat[i][k] * matrice[k][j];
            }
        }
    }

    return resultat;
}

Matrice Matrice::mat_translation(double x, double y, double z) {
    Matrice matrice(4, 4);

    matrice[0][0] = matrice[1][1] = matrice[2][2] = matrice[3][3] = 1;

    matrice[0][3] = x;
    matrice[1][3] = y;
    matrice[2][3] = z;

    return matrice;
}

Matrice Matrice::mat_translation(Vecteur vecteur) {
    Matrice matrice(4, 4);

    matrice[0][0] = matrice[1][1] = matrice[2][2] = matrice[3][3] = 1;

    matrice[0][3] = vecteur.x;
    matrice[1][3] = vecteur.y;
    matrice[2][3] = vecteur.z;

    return matrice;
}

Matrice Matrice::mat_homothetie(double x, double y, double z) {
    Matrice matrice(4, 4);

    matrice[0][0] = x;
    matrice[1][1] = y;
    matrice[2][2] = z;
    matrice[3][3] = 1;

    return matrice;
}

Matrice Matrice::mat_homothetie(Vecteur vecteur) {
    Matrice matrice(4, 4);

    matrice[0][0] = vecteur.x;
    matrice[1][1] = vecteur.y;
    matrice[2][2] = vecteur.z;
    matrice[3][3] = 1;

    return matrice;
}

Matrice Matrice::mat_rotation_x(double theta) {
    Matrice matrice(4, 4);

    matrice[0][0] = matrice[3][3] = 1;

    matrice[1][1] = matrice[2][2] = cos(theta);

    matrice[1][2] = -sin(theta);
    matrice[2][1] = sin(theta);

    return matrice;
}

Matrice Matrice::mat_rotation_y(double theta) {
    Matrice matrice(4, 4);

    matrice[1][1] = matrice[3][3] = 1;

    matrice[0][0] = matrice[2][2] = cos(theta);

    matrice[0][2] = sin(theta);
    matrice[2][0] = -sin(theta);

    return matrice;
}

Matrice Matrice::mat_rotation_z(double theta) {
    Matrice matrice(4, 4);

    matrice[2][2] = matrice[3][3] = 1;

    matrice[0][0] = matrice[1][1] = cos(theta);

    matrice[0][1] = -sin(theta);
    matrice[1][0] = sin(theta);

    return matrice;
}