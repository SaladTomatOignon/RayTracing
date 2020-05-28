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
        mat[i] = nullptr;
    }

    delete[] mat;
    mat = nullptr;
}

double* Matrice::operator[](int const& i) const {
    return mat[i];
}

Matrice Matrice::operator*(const Matrice& matrice) {
    Matrice resultat(lignes, colonnes);

    if (this->colonnes != matrice.lignes) {
        throw std::domain_error("Matrices incompatibles pour la multiplication");
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

Vecteur Matrice::operator*(Vecteur& vecteur) {
    double x = 0, y = 0, z = 0;

    if (this->colonnes != 4 && this->colonnes != 3) {
        throw std::domain_error("Matrice incompatible pour la multiplication");
    }

    x = mat[0][0] * vecteur.x + mat[0][1] * vecteur.y + mat[0][2] * vecteur.z;
    y = mat[1][0] * vecteur.x + mat[1][1] * vecteur.y + mat[1][2] * vecteur.z;
    z = mat[2][0] * vecteur.x + mat[2][1] * vecteur.y + mat[2][2] * vecteur.z;

    return Vecteur(x, y, z);
}

Matrice& Matrice::operator=(const Matrice& autre) {
    if (&autre != this) {
        lignes = autre.lignes;
        colonnes = autre.colonnes;

        /* S'assurer que 'this' a bien allou� ses tableaux */
        for (unsigned int i = 0; i < autre.lignes; i++) {
            for (unsigned int j = 0; j < autre.colonnes; j++) {
                mat[i][j] = autre.mat[i][j];
            }
        }
    }

    return *this;
}

Matrice Matrice::mat_identite(unsigned int taille) {
    Matrice identite(taille, taille);

    for (unsigned int i = 0; i < taille; i++) {
        identite.mat[i][i] = 1;
    }

    return identite;
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

Matrice Matrice::mat_rotation_axe(Vecteur axe, double theta) {
    Matrice matrice(3, 3);
    double c = cos(theta);
    double s = sin(theta);

    matrice[0][0] = pow(axe.x, 2) * (1.0 - c) + c;
    matrice[1][1] = pow(axe.y, 2) * (1.0 - c) + c;
    matrice[2][2] = pow(axe.z, 2) * (1.0 - c) + c;

    matrice[1][0] = axe.x * axe.y * (1.0 - c) + axe.z * s;
    matrice[0][1] = axe.x * axe.y * (1.0 - c) - axe.z * s;

    matrice[2][0] = axe.x * axe.z * (1.0 - c) - axe.y * s;
    matrice[0][2] = axe.x * axe.z * (1.0 - c) + axe.y * s;

    matrice[2][1] = axe.y * axe.z * (1.0 - c) + axe.x * s;
    matrice[1][2] = axe.y * axe.z * (1.0 - c) - axe.x * s;

    return matrice;
}