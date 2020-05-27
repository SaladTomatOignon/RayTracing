#ifndef DEF__GRILLE
#define DEF__GRILLE

#include "../scene/rectangle.h"
#include "../scene/camera.h"
#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"

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
        /**
         * @brief Renvoie le vecteur partant du centre de la grille et pointant vers le centre du pixel (i, j).
         * @param i Ligne du pixel (0 : en haut; max : en bas)
         * @param j Colonne du pixel (0 : à gauche; max : à droite)
         * @return Le vecteur du milieu de la grille vers le centre du pixel (i, j)
        */
        Vecteur centrePixel(unsigned int i, unsigned int j);
        /**
         * @brief Renvoie le vecteur partant du centre de la grille et pointant vers un point aléatoire du pixel (i, j).
         * @param i Ligne du pixel (0 : en haut; max : en bas)
         * @param j Colonne du pixel (0 : à gauche; max : à droite)
         * @return Le vecteur du milieu de la grille vers un point aléatoire du pixel (i, j)
        */
        Vecteur pointAleatoirePixel(unsigned int i, unsigned int j);
        void positionner(Camera camera);

        unsigned int resolution_l, resolution_h;

        double largeur, hauteur, distance_focale;
        Vecteur inclinaison_h, inclinaison_v;

    private:
        bool estPositionne = false;
        Point position;
};

#endif