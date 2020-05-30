#ifndef DEF__MATERIAU
#define DEF__MATERIAU

#include "../outils/couleur.h"

class Materiau {
    public:
        Materiau();
        Materiau(const Materiau& materiau);
        Materiau(Couleur couleur, int brillance, Couleur specularite, float coeffDiffusion, float reflexion, float coeffRefraction, float indiceRefraction);
        ~Materiau();

        Couleur couleur;
        Couleur specularite;
        int brillance;
        float coeffDiffusion;
        float reflexion;
        float coeffRefraction;
        float indiceRefraction;
};

#endif