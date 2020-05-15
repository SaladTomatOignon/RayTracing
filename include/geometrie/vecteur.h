#ifndef DEF__VECTEUR
#define DEF__VECTEUR

class Vecteur {
    public:
        Vecteur();
        Vecteur(double x, double y, double z);
        Vecteur(const Vecteur& vecteur);
        ~Vecteur();

        double x, y, z;
};

#endif