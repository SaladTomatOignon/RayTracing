#include "../../include/scene/triangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(Point(), rotation, materiau, forme2D = true) {
    this->a = Point(a);
    this->b = Point(b);
    this->c = Point(c);

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation) : Triangle(a, b, c, rotation, Materiau(), false) {

}

Triangle::Triangle(Point a, Point b, Point c, Vecteur rotation, Materiau materiau) : Triangle(a, b, c, rotation, materiau, false) {

}

Triangle::Triangle(const Triangle& tr) : Triangle(tr.a, tr.b, tr.c, tr.rotation, tr.materiau) {

}

Triangle::~Triangle() {

}

Triangle* Triangle::creerFormeCanonique() {
    // Triangle �quilat�ral de longueur racine de 5 centr� sur l'origine, dans le plan z = 0
    return new Triangle(Point(-1, -1, 0), Point(0, 1, 0), Point(1, -1, 0), Vecteur(), Materiau(), true);
}

Triangle* Triangle::getFormeCanonique() {
    return (Triangle*) formeCanonique;
}

Point Triangle::getCentre() {
    return Point(); // TODO
}

void Triangle::homothetieFormeCanonique() {

}

void Triangle::rotationFormeCanonique() {
    Md = Md * Matrice::mat_rotation_x(rotation.x);
    Mi = Matrice::mat_rotation_x(-rotation.x) * Mi;
    Mn = Mn * Matrice::mat_rotation_x(rotation.x);

    Md = Md * Matrice::mat_rotation_y(rotation.y);
    Mi = Matrice::mat_rotation_y(-rotation.y) * Mi;
    Mn = Mn * Matrice::mat_rotation_y(rotation.y);

    Md = Md * Matrice::mat_rotation_z(rotation.z);
    Mi = Matrice::mat_rotation_z(-rotation.z) * Mi;
    Mn = Mn * Matrice::mat_rotation_z(rotation.z);
}

void Triangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Triangle::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
    Vecteur edge1, edge2, h, s, q;
    double a, f, u, v;

    edge1 = Vecteur(b.x, b.y, b.z) - Vecteur(this->a.x, this->a.y, this->a.z);
    edge2 = Vecteur(c.x, c.y, c.z) - Vecteur(this->a.x, this->a.y, this->a.z);

    h = r.direction.prodVectoriel(edge2);
    a = edge1.prodScalaire(h);

    if (a > -_EPSILON_ && a < _EPSILON_) {
        return false;
    }

    f = 1.0 / a;
    s = Vecteur(r.origine.x, r.origine.y, r.origine.z) - Vecteur(this->a.x, this->a.y, this->a.z);;
    u = f * (s.prodScalaire(h));

    if (u < 0.0 || u > 1.0) {
        return false;
    }

    q = s.prodVectoriel(edge1);
    v = f * r.direction.prodScalaire(q);

    if (v < 0.0 || u + v > 1.0) {
        return false;
    }

    double t = f * edge2.prodScalaire(q);
    if (t > _EPSILON_) {
        intersection = r.origine + t * r.direction;
        normale = edge2.prodVectoriel(edge1).unitaire();
        return true;
    } else {
        return false;
    }
}

bool Triangle::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!intersectionCanonique(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}