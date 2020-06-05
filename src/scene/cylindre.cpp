#include "../../include/scene/cylindre.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(Point(), rotation, materiau) {
    this->a = Point(a);
    this->b = Point(b);
    this->rayon = rayon;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation, Materiau materiau) : Cylindre(a, b, rayon, rotation, materiau, false) {

}

Cylindre::Cylindre(Point a, Point b, double rayon, Vecteur rotation) : Cylindre(a, b, rayon, rotation, Materiau(), false) {

}

Cylindre::Cylindre(const Cylindre& cylindre) : Cylindre(cylindre.a, cylindre.b, cylindre.rayon, cylindre.rotation, cylindre.materiau) {

}

Cylindre::~Cylindre() {

}

Cylindre* Cylindre::creerFormeCanonique() {
    /* Cylindre centré à l'origine de rayon 1 et de hauteur 2 */
    return new Cylindre(
        Point(0, -1, 0),
        Point(0, 1, 0),
        1,
        Vecteur(0, 0, 0),
        Materiau(),
        true
    );
}

Cylindre* Cylindre::getFormeCanonique() {
    return (Cylindre*) formeCanonique;
}

Point Cylindre::getCentre() {
    return Point(
        (a.x + b.x) / 2,
        (a.y + b.y) / 2,
        (a.z + b.z) / 2
    );
}

void Cylindre::homothetieFormeCanonique() {

}

void Cylindre::rotationFormeCanonique() {
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

void Cylindre::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Cylindre::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
    r.direction = r.direction.unitaire();
    double a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z);
    double b = 2 * (r.direction.x * (r.origine.x - centre.x) + r.direction.z * (r.origine.z - centre.z));
    double c = (r.origine.x - centre.x) * (r.origine.x - centre.x) + (r.origine.z - centre.z) * (r.origine.z - centre.z) - (rayon * rayon);

    double delta = b * b - 4 * (a * c);
    if (fabs(delta) < _EPSILON_) {
        return false;
    }
    if (delta < 0.0) {
        return false;
    }

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
    double t;

    if (t1 > t2) t = t2;
    else t = t1;

    double R = r.origine.y + t * r.direction.y;

    if ((R >= centre.y) && (R <= centre.y + 1)) {
        intersection = r.origine + t * r.direction;
        normale = Vecteur(intersection.x - centre.x, 0, intersection.z - centre.z).unitaire();
        return t;
    }
    return false;
}

bool Cylindre::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!intersectionCanonique(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}