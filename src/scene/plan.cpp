#include "../../include/scene/plan.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

#include <stdexcept>

Plan::Plan(Point centre, Vecteur normale, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau, forme2D = true) {
    Vecteur vecteurNul = normale - normale.unitaire();

    if (abs(Vecteur::sommeCoeff(vecteurNul)) > _ZERO_) {
        throw std::invalid_argument("La normale du plan doit être un vecteur unitaire");
    }

    this->normale = normale;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Plan::Plan(Point centre, Vecteur normale, Vecteur rotation, Materiau materiau) : Plan(centre, normale, rotation, materiau, false) {

}

Plan::Plan(Point centre, Vecteur normale, Vecteur rotation) : Plan(centre, normale, rotation, Materiau(), false) {

}

Plan::Plan(const Plan& plan) : Plan(plan.centre, plan.normale, plan.rotation, plan.materiau) {

}

Plan::~Plan() {

}

Plan* Plan::creerFormeCanonique() {
    // Plan passant par l'origine et parrallèle à l'axe x
    return new Plan(Point(0, 0, 0), Vecteur(0, 1, 0), Vecteur(0, 0, 0), Materiau(), true);
}

Plan* Plan::getFormeCanonique() {
    return (Plan*) formeCanonique;
}

Point Plan::getCentre() {
    return centre;
}

void Plan::homothetieFormeCanonique() {

}

void Plan::rotationFormeCanonique() {
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

void Plan::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
}

bool Plan::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
    Vecteur u = r.direction.unitaire();
    double m = this->normale.prodScalaire(u);

    if (std::abs(m) < _EPSILON_) {
        return false;
    }

    Point L = r.origine - centre;
    Vecteur vL = Vecteur(L.x, L.y, L.z);
    double d = this->normale.prodScalaire(vL);
    double t = -d / m;

    if (t > 0) {
        intersection = r.origine + t * u;
        normale = Vecteur(this->normale);
        return true;
    }

    return false;
}

bool Plan::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!intersectionCanonique(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}