#ifndef DEF__CYLINDRE
#define DEF__CYLINDRE

#include "../scene/forme.h"
#include "../scene/couleur.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Cylindre : public Forme {
    public:
        Cylindre(Point a, Point b, double rayon);
        Cylindre(Point a, Point b, double rayon, Couleur couleur);
        Cylindre(const Cylindre& cylindre);
        ~Cylindre();

        virtual Cylindre* clone() const {
            return new Cylindre(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon r, Point& intersection, Vecteur& normale) override;

    private:
        Point a, b;
        double rayon;

        Cylindre(Point a, Point b, double rayon, Couleur couleur, bool estCanonique);

        virtual Cylindre* creerFormeCanonique() override;
        virtual Cylindre* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif