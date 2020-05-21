#ifndef DEF__VECTEUR
#define DEF__VECTEUR

class Vecteur {
    public:
        Vecteur();
        Vecteur(double x, double y, double z);
        Vecteur(const Vecteur& vecteur);
        ~Vecteur();

        bool operator==(const Vecteur& autre);
        bool operator!=(const Vecteur& autre);
        Vecteur operator+(const Vecteur& autre);
        Vecteur operator-(const Vecteur& autre);
        friend Vecteur operator*(const double scalaire, const Vecteur& u);
        double prodScalaire(Vecteur& v);
        Vecteur prodVectoriel(Vecteur& v);
        Vecteur unitaire();

        double x, y, z;
};

#endif