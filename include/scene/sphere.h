#ifndef DEF__SPHERE
#define DEF__SPHERE

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Sphere : public Forme {
    public:
        Sphere(Point centre, double rayon, Vecteur rotation);
        Sphere(Point centre, double rayon, Vecteur rotation, Materiau materiau);
        Sphere(Point centre, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique);
        Sphere(const Sphere& sphere);
        ~Sphere();

        virtual Sphere* clone() const {
            return new Sphere(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

        double rayon;

    private:
        virtual Sphere* creerFormeCanonique() override;
        virtual Sphere* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif