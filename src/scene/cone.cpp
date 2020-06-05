#include "../../include/scene/cone.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

Cone::Cone(Point centre, double rayon, double hauteur, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau, forme2D = true) {
    this->rayon = rayon;
    this->hauteur = hauteur;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Cone::Cone(Point centre, double rayon, double hauteur, Vecteur rotation) : Cone(centre, rayon, hauteur, rotation, Materiau(), false) {

}

Cone::Cone(Point centre, double rayon, double hauteur, Vecteur rotation, Materiau materiau) : Cone(centre, rayon, hauteur, rotation, materiau, false) {

}

Cone::Cone(const Cone& cone) : Cone(cone.centre, cone.rayon, cone.hauteur, cone.rotation, cone.materiau) {

}

Cone::~Cone() {

}

Cone* Cone::creerFormeCanonique() {
    // Cone centré en (0, 0, 0) de rayon 1 et de hauteur 1.
    return new Cone(Point(0, 0, 0), 1, 1, Vecteur(0, 0, 0), Materiau(), true);
}

Cone* Cone::getFormeCanonique() {
    return (Cone*)formeCanonique;
}

Point Cone::getCentre() {
    return Point(centre);
}

void Cone::homothetieFormeCanonique() {

}

void Cone::rotationFormeCanonique() {
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

void Cone::translationFormeCanonique() {
    Point centre = getCentre();

    Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
    Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
    Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Cone::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
    r.direction = r.direction.unitaire();

    double A = r.origine.x - centre.x;
    double B = r.origine.z - centre.z;
    double D = hauteur - r.origine.y + centre.y;

    double tan = (rayon / hauteur) * (rayon / hauteur);

    double a = (r.direction.x * r.direction.x) + (r.direction.z * r.direction.z) - (tan * (r.direction.y * r.direction.y));
    double b = (2 * A * r.direction.x) + (2 * B * r.direction.z) + (2 * tan * D * r.direction.y);
    double c = (A * A) + (B * B) - (tan * (D * D));

    double delta = b * b - 4 * (a * c);
    if (std::abs(delta) < _EPSILON_) {
        return false;
    }

    double racine1 = (-b - sqrt(delta)) / (2 * a);
    double racine2 = (-b + sqrt(delta)) / (2 * a);
    double t;

    if (racine1 > racine2) {
        t = racine2;
    } else {
        t = racine1;
    }

    double R = r.origine.y + t * r.direction.y;

    if ((R > centre.y) && (R < centre.y + hauteur)) {
        intersection = r.origine + t * r.direction;

        double R = sqrt((intersection.x - centre.x) * (intersection.x - centre.x) + (intersection.z - centre.z) * (intersection.z - centre.z));
        Vecteur n = Vecteur(intersection.x - centre.x, R * (rayon / hauteur), intersection.z - centre.z);
        normale = n.unitaire();

        return true;
    }

    return false;
}

bool Cone::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
    Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

    if (!intersectionCanonique(rCanonique, intersection, normale)) {
        return false;
    }

    intersection = Point(Md * intersection);
    normale = Mn * normale;
    normale = normale.unitaire();

    return true;
}