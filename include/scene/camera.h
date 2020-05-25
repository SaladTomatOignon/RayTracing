#ifndef DEF__CAMERA
#define DEF__CAMERA

#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"

class Camera {
    public:
        Camera();
        Camera(const Camera& camera);
        Camera(Point position, Vecteur orientation);
        ~Camera();

        enum class DIRECTION {
            GAUCHE,
            HAUT,
            DROITE,
            BAS,
            DEVANT,
            DERRIERE,
            NONE
        };

        /**
         * @brief D�cale de un cran (une unit�e) la position de la cam�ra vers la direction sp�cifi�e.
         * N'affecte pas la direction.
         * @param direction La direction vers laquelle translater la cam�ra.
        */
        void translater(DIRECTION direction);
        /**
         * @brief D�cale de un cran (une unit�e) l'orientation de la cam�ra vers la direction sp�cifi�e.
         * N'affecte pas la position.
         * @param direction La direction vers laquelle orienter la cam�ra.
        */
        void orienter(DIRECTION direction);

        Point position;
        Vecteur orientation;
};

#endif