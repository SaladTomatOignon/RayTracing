#ifndef DEF__PIXEL
#define DEF__PIXEL

class Couleur {
    public:
        Couleur();
        Couleur(unsigned char r, unsigned char g, unsigned char b);
        Couleur(const Couleur& pixel);
        ~Couleur();

        unsigned char r, g, b;
};

#endif