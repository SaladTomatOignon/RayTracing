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

        Point position;
        Vecteur orientation;
};

#endif