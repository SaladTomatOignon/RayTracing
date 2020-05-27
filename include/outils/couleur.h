#ifndef DEF__PIXEL
#define DEF__PIXEL

class Couleur {
    public:
        Couleur();
        Couleur(unsigned int r, unsigned int g, unsigned int b);
        Couleur(const Couleur& pixel);
        ~Couleur();

        Couleur operator*(const double& reel);
        Couleur operator+(const Couleur& autre);
        Couleur operator/(const double& reel);

        /**
         * @brief Renvoie la m�me couleur avec un seuil maximum de 255 pour la valeur de chaque composante.
         * Note : Vu qu'une composante est un entier non sign�, seul le maximum est born�.
        */
        Couleur clamp();

        unsigned int r, g, b;
};

#endif