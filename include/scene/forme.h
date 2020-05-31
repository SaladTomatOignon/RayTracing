#ifndef DEF__FORME
#define DEF__FORME

#include "../geometrie/matrice.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"
#include "../outils/materiau.h"

class Forme {
    public:
        Forme();
        Forme(Materiau couleur, bool forme2D = false);
        ~Forme();

        virtual Forme* clone() const = 0;
        virtual Point getCentre() = 0;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) = 0;

        Materiau materiau;
        bool forme2D;
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
        Matrice Mn = Matrice::mat_identite(4);
};

#endif