#ifndef DEF__TRIANGLE
#define DEF__TRIANGLE

#include "../scene/forme.h"
#include "../geometrie/point.h"

class Triangle : public Forme {
    public:
        Triangle(Point a, Point b, Point c);
        Triangle(const Triangle& tr);
        ~Triangle();

        virtual Triangle* clone() const {
            return new Triangle(*this);
        };

    private:
        Point a, b, c;

        Triangle(Point a, Point b, Point c, bool estCanonique);

        virtual Triangle* creerFormeCanonique() override;
        virtual Triangle* getFormeCanonique() override;
        virtual Point getCentre() override;
        virtual void homothetieFormeCanonique() override;
        virtual void rotationFormeCanonique() override;
        virtual void translationFormeCanonique() override;
};

#endif