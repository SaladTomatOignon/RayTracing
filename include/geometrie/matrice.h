#ifndef DEF__MATRICE
#define DEF__MATRICE

#include "../geometrie/vecteur.h"

class Matrice {
    public:
        Matrice(unsigned int nb_lignes, unsigned int nb_colonnes);
        Matrice(const Matrice& image);
        ~Matrice();

        double* operator[](int const& i);
        Matrice operator*(Matrice matrice);

        static Matrice mat_translation(double x = 0, double y = 0, double z = 0);
        static Matrice mat_translation(Vecteur vecteur);
        static Matrice mat_homothetie(double x = 0, double y = 0, double z = 0);
        static Matrice mat_homothetie(Vecteur vecteur);
        static Matrice mat_rotation_x(double theta);
        static Matrice mat_rotation_y(double theta);
        static Matrice mat_rotation_z(double theta);

    private:
        unsigned int lignes, colonnes;
        double** mat;
};

#endif