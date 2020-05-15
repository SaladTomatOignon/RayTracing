#ifndef DEF__TRIANGLE
#define DEF__TRIANGLE

#include "../scene/forme.h"
#include "../geometrie/point.h"

class Triangle : public Forme {
    public:
        Triangle(Point a, Point b, Point c);
        Triangle(const Triangle& tr);
        ~Triangle();

        virtual Triangle* clone() const override;

    private:
        Point a, b, c;
};

#endif