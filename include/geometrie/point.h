#ifndef DEF__POINT
#define DEF__POINT

#include "../geometrie/vecteur.h"

class Point {
    public:
        Point();
        Point(double x, double y, double z);
        Point(const Point& point);
        ~Point();

        Point operator+(const Vecteur& v);

        double x, y, z;
};

#endif