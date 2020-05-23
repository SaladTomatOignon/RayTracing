#ifndef DEF__TRIANGLE
#define DEF__TRIANGLE

#include "../scene/forme.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"
#include "../outils/couleur.h"

class Triangle : public Forme {
    public:
        Triangle(Point a, Point b, Point c);
        Triangle(Point a, Point b, Point c, Couleur couleur);
        Triangle(const Triangle& tr);
        ~Triangle();

        virtual Triangle* clone() const {
            return new Triangle(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon r, Point& intersection, Vecteur& normale) override;

    private:
        Point a, b, c;

        Triangle(Point a, Point b, Point c, Couleur couleur, bool estCanonique);

        virtual Triangle* creerFormeCanonique() override;
        virtual Triangle* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif