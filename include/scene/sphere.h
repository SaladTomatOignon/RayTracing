#ifndef DEF__SPHERE
#define DEF__SPHERE

#include "../scene/forme.h"
#include "../geometrie/point.h"

class Sphere : public Forme {
    public:
        Sphere(Point centre, double rayon);
        Sphere(const Sphere& sphere);
        ~Sphere();

        virtual Sphere* clone() const {
            return new Sphere(*this);
        };

    private:
        Point centre;
        double rayon;

        Sphere(Point centre, double rayon, bool estCanonique);

        virtual Sphere* creerFormeCanonique() override;
        virtual Sphere* getFormeCanonique() override;
        virtual Point getCentre() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif