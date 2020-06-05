#include "../../include/scene/rectangle.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Rectangle::Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau, forme2D = true) {
    this->normale = normale;
    this->largeur = largeur;
    this->longueur = longueur;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Rectangle::Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation, Materiau materiau) : Rectangle(centre, normale, largeur, longueur, rotation, materiau, false) {

}

Rectangle::Rectangle(Point centre, Vecteur normale, double largeur, double longueur, Vecteur rotation) : Rectangle(centre, normale, largeur, longueur, rotation, Materiau(), false) {

}

Rectangle::Rectangle(const Rectangle& rect) : Rectangle(rect.centre, rect.normale, rect.largeur, rect.longueur, rect.rotation, rect.materiau) {

}

Rectangle::Rectangle(Point a, Point b, Point c, Point d, Vecteur rotation) : Rectangle(Point(), Vecteur(), 0, 0, Vecteur()) {
    centre = Point((a.x + b.x + c.x + d.x) / 4, (a.y + b.y + c.y + d.y) / 4, (a.z + b.z + c.z + d.z) / 4);

    Vecteur directeur1 = Point::creerVecteur(a, b);
    Vecteur directeur2 = Point::creerVecteur(a, d);
    normale = directeur1.prodVectoriel(directeur2);

    largeur = 1; // TODO
    longueur = 1; // TODO
}

Rectangle::~Rectangle() {

}

Rectangle* Rectangle::creerFormeCanonique() {
    // Carré de côté 2 centré sur l'origine, dans le plan z = 0
    return new Rectangle(Point(0, 0, 0), Vecteur(0, 0, 1), 2, 2, Vecteur(), Materiau(), true);
}

Rectangle* Rectangle::getFormeCanonique() {
    return (Rectangle*) formeCanonique;
}

Point Rectangle::getCentre() {
    return centre;
}

void Rectangle::homothetieFormeCanonique() {
    Rectangle* rectangleCanonique = getFormeCanonique();

    Md = Md * Matrice::mat_homothetie(largeur / rectangleCanonique->largeur, longueur / rectangleCanonique->longueur, 1);
    Mi = Matrice::mat_homothetie(1 / (largeur / rectangleCanonique->largeur), 1 / (longueur / rectangleCanonique->longueur), 1) * Mi;
    Mn = Mn * Matrice::mat_homothetie(longueur / rectangleCanonique->longueur, largeur / rectangleCanonique->largeur, (largeur / rectangleCanonique->largeur) * (longueur / rectangleCanonique->longueur));
}

void Rectangle::rotationFormeCanonique() {
    // TODO : Ramener le plan aligné sur l'axe Z

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

void Rectangle::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Rectangle::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
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

        if (-1 < intersection.y && intersection.y < 1) {
            if (-1 < intersection.x && intersection.x < 1) {
                return true;
            }
        }

        return false;
    }

    return false;
}

bool Rectangle::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!intersectionCanonique(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}