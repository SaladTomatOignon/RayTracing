#ifndef DEF__SPHERE
#define DEF__SPHERE

#include "../scene/forme.h"
#include "../geometrie/point.h"

class Sphere : public Forme {
    public:
        Sphere(Point centre, double rayon);
        Sphere(const Sphere& sphere);
        ~Sphere();

        virtual Sphere* clone() const override;

    private:
        Point centre;
        double rayon;
};

#endif