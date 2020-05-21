#ifndef DEF__GRILLE
#define DEF__GRILLE

#include "../scene/rectangle.h"
#include "../scene/camera.h"
#include "../geometrie/point.h"

class Grille {
    public:
        Grille();
        Grille(double largeur, double hauteur, unsigned int resolution_l, unsigned int resolution_h, double distance_focale, Vecteur inclinaison);
        Grille(const Grille& grille);
        ~Grille();

        Rectangle at(unsigned int i, unsigned int j);
        void positionner(Camera camera);

    private:
        double largeur, hauteur, distance_focale;
        unsigned int resolution_l, resolution_h;
        Vecteur inclinaison_h, inclinaison_v;
        bool estPositionne = false;
        Point position;
};

#endif