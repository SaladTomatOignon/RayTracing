#include "../../include/scene/plan.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

#include <stdexcept>

Plan::Plan(Point centre, Vecteur normale, Materiau materiau, bool estCanonique) : Forme(materiau, forme2D = true) {
    Vecteur vecteurNul = normale - normale.unitaire();

    if (abs(Vecteur::sommeCoeff(vecteurNul)) > _ZERO_) {
        throw std::invalid_argument("La normale du plan doit �tre un vecteur unitaire");
    }

    this->centre = centre;
    this->normale = normale;
}

Plan::Plan(Point centre, Vecteur normale, Materiau materiau) : Plan(centre, normale, materiau, false) {

}

Plan::Plan(Point centre, Vecteur normale) : Plan(centre, normale, Materiau(), false) {

}

Plan::Plan(const Plan& plan) : Plan(plan.centre, plan.normale, plan.materiau) {

}

Plan::~Plan() {

}

Plan* Plan::creerFormeCanonique() {
    // Plan passant par l'origine et parralelle � l'axe x
    return new Plan(Point(0, 0, 0), Vecteur(0, 1, 0), Materiau(), true);
}

Plan* Plan::getFormeCanonique() {
    return (Plan*)formeCanonique;
}

Point Plan::getCentre() {
    return centre;
}

void Plan::homothetieFormeCanonique() {

}

void Plan::rotationFormeCanonique() {

}

void Plan::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Mi * Matrice::mat_translation(-centre.x, -centre.y, -centre.z);
}

bool Plan::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
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