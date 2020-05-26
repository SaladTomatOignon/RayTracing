#ifndef DEF__VECTEUR
#define DEF__VECTEUR

#define _EPSILON_ (1.e-6)
#define _ZERO_ (0 + _EPSILON_)

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

        /**
         * @brief Renvoie la somme des coefficients du vecteur en param�tre.
         * @param vecteur 
         * @return La somme des coefficients du vecteur.
        */
        static double sommeCoeff(Vecteur& vecteur);

        double x, y, z;
};

#endif