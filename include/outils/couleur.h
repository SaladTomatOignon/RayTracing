#ifndef DEF__PIXEL
#define DEF__PIXEL

class Couleur {
    public:
        Couleur();
        Couleur(float r, float g, float b);
        Couleur(const Couleur& pixel);
        ~Couleur();

        Couleur operator*(const double& reel);
        Couleur operator+(const Couleur& autre);
        Couleur operator/(const double& reel);

        /**
         * @brief Renvoie la même couleur avec un seuil maximum de 255 pour la valeur de chaque composante.
         * Note : Vu qu'une composante est un entier non signé, seul le maximum est borné.
        */
        Couleur clamp();

        float r, g, b;
};

#endif