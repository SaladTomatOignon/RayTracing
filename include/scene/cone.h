#ifndef DEF__CONE
#define DEF__CONE

#include "../scene/forme.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"
#include "../outils/materiau.h"

class Cone : public Forme {
    public:
        Cone(Point centre, double rayon, double hauteur, Vecteur rotation);
        Cone(Point centre, double rayon, double hauteur, Vecteur rotation, Materiau materiau);
        Cone(const Cone& cone);
        ~Cone();

        virtual Cone* clone() const {
            return new Cone(*this);
        };

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

    private:
        double rayon, hauteur;

        Cone(Point centre, double rayon, double hauteur, Vecteur rotation, Materiau materiau, bool estCanonique);

        virtual Cone* creerFormeCanonique() override;
        virtual Cone* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
        bool intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale);
};

#endif