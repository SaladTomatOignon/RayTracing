#ifndef DEF__PLAN
#define DEF__PLAN

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Plan : public Forme {
    public:
        Plan(Point centre, Vecteur normale, Vecteur rotation);
        Plan(Point centre, Vecteur normale, Vecteur rotation, Materiau materiau);
        Plan(const Plan& plan);
        ~Plan();

        virtual Plan* clone() const {
            return new Plan(*this);
        }

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

    private:
        Vecteur normale;

        Plan(Point centre, Vecteur normale, Vecteur rotation, Materiau materiau, bool estCanonique);

        virtual Plan* creerFormeCanonique() override;
        virtual Plan* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
        bool intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale);
};

#endif