#ifndef DEF__IMAGE
#define DEF__IMAGE

#include "../outils/couleur.h"

class Image {
    public:
        Image(unsigned int largeur, unsigned int hauteur);
        Image(const Image& image);
        ~Image();

        struct m_Couleur {
            double r;
            double g;
            double b;
        };

        Image& operator=(Image const& autre);

        Couleur get(unsigned i, unsigned j);
        m_Couleur* getData();
        void set(unsigned i, unsigned j, Couleur& couleur);

        /*!
         * \brief Cr�e un nouveau fichier au format ppm contenant les pixels associ� � cette image.
         * Cr�e le fichier `fileName` � l'endroit o� est ex�cut� le programme.
         *
         * \param fileName Le nom du fichier � cr�er.
         */
        void exportPPM(const char* fileName);

        unsigned int largeur, hauteur;
        m_Couleur* valeurs;
};

#endif