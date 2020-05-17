#ifndef DEF__FORME
#define DEF__FORME

#include "../geometrie/matrice.h"

class Forme {
    public:
        Forme();
        ~Forme();

        virtual Forme* clone() const = 0;

    protected:
        Matrice Md = Matrice(4, 4);
        Matrice Mi = Matrice(4, 4);
};

#endif