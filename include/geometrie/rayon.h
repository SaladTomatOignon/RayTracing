#ifndef DEF__RAYON
#define DEF__RAYON

#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"

class Rayon {
    public:
        Rayon();
        Rayon(Point o, Vecteur u);
        Rayon(const Rayon& rayon);
        ~Rayon();

        Point origine;
        Vecteur direction;
        
};

#endif