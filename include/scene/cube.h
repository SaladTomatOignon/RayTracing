#ifndef DEF__CUBE
#define DEF__CUBE

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Cube : public Forme {
    public:
        Cube(Point centre, double taille, Vecteur rotation);
        Cube(Point centre, double taille, Vecteur rotation, Materiau materiau);
        Cube(Point centre, double taille, Vecteur rotation, Materiau materiau, bool estCanonique);
        Cube(const Cube& sphere);
        ~Cube();

        virtual Cube* clone() const {
            return new Cube(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

        double taille;

    private:
        virtual Cube* creerFormeCanonique() override;
        virtual Cube* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
        bool intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale);
};

#endif