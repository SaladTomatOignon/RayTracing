#ifndef DEF__LUMIERE
#define DEF__LUMIERE

#include "../geometrie/point.h"

class Lumiere {
    public:
        Lumiere();
        Lumiere(const Lumiere& lumiere);
        Lumiere(Point position, double intensite);
        ~Lumiere();

    private:
        Point position;
        double intensite;
};

#endif