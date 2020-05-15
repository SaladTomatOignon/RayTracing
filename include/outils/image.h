#ifndef DEF__IMAGE
#define DEF__IMAGE

#include "../scene/pixel.h"

class Image {
    public:
        Image(unsigned int largeur, unsigned int hauteur);
        Image(const Image& image);
        ~Image();

        Pixel* operator[](int const& i);

        /*!
         * \brief Cr�e un nouveau fichier au format ppm contenant les pixels associ� � cette image.
         * Cr�e le fichier `fileName` � l'endroit o� est ex�cut� le programme.
         *
         * \param fileName Le nom du fichier � cr�er.
         */
        void exportPPM(const char* fileName);

    private:
        unsigned int largeur, hauteur;
        Pixel** valeurs;
};

#endif