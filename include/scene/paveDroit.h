#ifndef DEF__PAVE_DROIT
#define DEF__PAVE_DROIT

#include "../scene/forme.h"
#include "../scene/cube.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class PaveDroit : public Forme {
public:
    PaveDroit(Point centre, double largeur, double hauteur, double profondeur, Vecteur rotation);
    PaveDroit(Point centre, double largeur, double hauteur, double profondeur, Vecteur rotation, Materiau materiau);
    PaveDroit(const PaveDroit& paveDroit);
    ~PaveDroit();

    virtual PaveDroit* clone() const {
        return new PaveDroit(*this);
    };

    virtual Point getCentre() override;
    virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

private:
    double largeur, hauteur, profondeur;

    virtual Cube* creerFormeCanonique() override;
    virtual Cube* getFormeCanonique() override;
    virtual void homothetieFormeCanonique() override;
    virtual void rotationFormeCanonique() override;
    virtual void translationFormeCanonique() override;
};

#endif