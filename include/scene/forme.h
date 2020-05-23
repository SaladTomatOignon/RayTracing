#ifndef DEF__FORME
#define DEF__FORME

#include "../geometrie/matrice.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"
#include "../outils/couleur.h"

class Forme {
    public:
        Forme();
        Forme(Couleur couleur);
        ~Forme();

        virtual Forme* clone() const = 0;
        virtual Point getCentre() = 0;
        virtual bool intersection(Rayon r, Point& intersection, Vecteur& normale) = 0;

        Couleur couleur;
    protected:
        virtual Forme* creerFormeCanonique() = 0;
        virtual Forme* getFormeCanonique() = 0;
        void initialiserMatricesTransformation();
        virtual void homothetieFormeCanonique() = 0;
        virtual void rotationFormeCanonique() = 0;
        virtual void translationFormeCanonique() = 0;

        Forme* formeCanonique;
        Matrice Md = Matrice::mat_identite(4);
        Matrice Mi = Matrice::mat_identite(4);
};

#endif