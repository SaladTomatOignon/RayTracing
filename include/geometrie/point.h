#ifndef DEF__POINT
#define DEF__POINT

class Point {
    public:
        Point();
        Point(double x, double y, double z);
        Point(const Point& point);
        ~Point();

        double x, y, z;
};

#endif