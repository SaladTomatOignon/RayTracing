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
         * @brief Décale de un cran (une unitée) la position de la caméra vers la direction spécifiée.
         * N'affecte pas la direction.
         * @param direction La direction vers laquelle translater la caméra.
        */
        void translater(DIRECTION direction);
        /**
         * @brief Décale de un cran (une unitée) l'orientation de la caméra vers la direction spécifiée.
         * N'affecte pas la position.
         * @param direction La direction vers laquelle orienter la caméra.
        */
        void orienter(DIRECTION direction);

        Point position;
        Vecteur orientation;
};

#endif