#ifndef DEF__CYLINDRE
#define DEF__CYLINDRE

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Cylindre : public Forme {
    public:
        Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation);
        Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation, Materiau materiau);
        Cylindre(const Cylindre& cylindre);
        ~Cylindre();

        virtual Cylindre* clone() const {
            return new Cylindre(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

    private:
        double rayon, hauteur;

        Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique);

        virtual Cylindre* creerFormeCanonique() override;
        virtual Cylindre* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
        bool intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale);
};

#endif