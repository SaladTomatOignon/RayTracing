#ifndef DEF__RECTANGLE
#define DEF__RECTANGLE

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Rectangle : public Forme {
    public:
        Rectangle(Point a, Point b, Point c, Point d, Vecteur rotation);
        Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation);
        Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation, Materiau materiau);
        Rectangle(const Rectangle& rect);
        ~Rectangle();

        virtual Rectangle* clone() const {
            return new Rectangle(*this);
        }

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

    private:
        Vecteur normale;
        double largeur, longueur;

        Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation, Materiau materiau, bool estCanonique);

        virtual Rectangle* creerFormeCanonique() override;
        virtual Rectangle* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
        bool intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale);
};

#endif