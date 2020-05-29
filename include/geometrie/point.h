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
        Point operator-(const Point& p);
        Point operator-(const Vecteur& v);

        static Vecteur creerVecteur(Point& a, Point& b);
        double distance(Point& a);
        double distance2(Point& a);

        double x, y, z;
};

#endif