#ifndef DEF__PLAN
#define DEF__PLAN

#include "../scene/forme.h"
#include "../outils/materiau.h"
#include "../geometrie/point.h"
#include "../geometrie/rayon.h"

class Plan : public Forme {
    public:
        Plan(Point centre, Vecteur normale);
        Plan(Point centre, Vecteur normale, Materiau materiau);
        Plan(const Plan& plan);
        ~Plan();

        virtual Plan* clone() const {
            return new Plan(*this);
        }

        virtual Point getCentre() override;
        virtual bool intersection(Rayon& r, Point& intersection, Vecteur& normale) override;

    private:
        Point centre;
        Vecteur normale;

        Plan(Point centre, Vecteur normale, Materiau materiau, bool estCanonique);

        virtual Plan* creerFormeCanonique() override;
        virtual Plan* getFormeCanonique() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif