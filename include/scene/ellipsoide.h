#ifndef DEF__ELLIPSOIDE
#define DEF__ELLIPSOIDE

#include "../scene/forme.h"
#include "../scene/sphere.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Ellipsoide : public Forme {
public:
    Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC, Vecteur rotation);
    Ellipsoide(Point centre, double rayonA, double rayonB, double rayonC, Vecteur rotation, Materiau materiau);
    Ellipsoide(const Ellipsoide& sphere);
    ~Ellipsoide();

    virtual Ellipsoide* clone() const {
        return new Ellipsoide(*this);
    };

    virtual Point getCentre() override;
    virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

private:
    double rayonA, rayonB, rayonC;

    virtual Sphere* creerFormeCanonique() override;
    virtual Sphere* getFormeCanonique() override;
    virtual void homothetieFormeCanonique() override;
    virtual void rotationFormeCanonique() override;
    virtual void translationFormeCanonique() override;
};

#endif