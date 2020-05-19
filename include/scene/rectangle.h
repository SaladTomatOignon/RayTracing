#ifndef DEF__RECTANGLE
#define DEF__RECTANGLE

#include "../scene/forme.h"
#include "../geometrie/point.h"

class Rectangle : public Forme {
    public:
        Rectangle(Point a, Point b, Point c, Point d);
        Rectangle(const Rectangle& rect);
        ~Rectangle();

        virtual Rectangle* clone() const {
            return new Rectangle(*this);
        }

    private:
        Point a, b, c, d;
};

#endif