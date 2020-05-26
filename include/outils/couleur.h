#ifndef DEF__PIXEL
#define DEF__PIXEL

class Couleur {
    public:
        Couleur();
        Couleur(unsigned char r, unsigned char g, unsigned char b);
        Couleur(const Couleur& pixel);
        ~Couleur();

        Couleur operator*(const double& reel);
        Couleur operator+(const Couleur& autre);

        unsigned char r, g, b;
};

#endif