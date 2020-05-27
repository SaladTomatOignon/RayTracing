#ifndef DEF__MATERIAU
#define DEF__MATERIAU

#include "../outils/couleur.h"

class Materiau {
    public:
        Materiau();
        Materiau(const Materiau& materiau);
        Materiau(Couleur couleur, int brillance, Couleur specularite);
        ~Materiau();

        Couleur couleur;
        Couleur specularite;
        int brillance;
};

#endif