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

        /**
         * @brief Renvoie la surface de la grille correspondant au pixel de l'image.
         * Le point (0,0) correspond au pixel "en haut à gauche" de la grille et le point(max, max) au pixel "en bas à droite".
         * @param i La ligne du pixel
         * @param j La colonne de la grille
         * @return Un rectangle correspondant à la surface du pixel de la grille.
        */
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