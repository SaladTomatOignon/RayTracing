#include "../../include/scene/cylindre.h"
#include "../../include/outils/materiau.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"

#include <math.h>

Cylindre::Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau) {
    this->hauteur = hauteur;
    this->rayon = rayon;

    if (!estCanonique) {
        initialiserMatricesTransformation();
    }
}

Cylindre::Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation, Materiau materiau) : Cylindre(centre, hauteur, rayon, rotation, materiau, false) {

}

Cylindre::Cylindre(Point centre, double hauteur, double rayon, Vecteur rotation) : Cylindre(centre, hauteur, rayon, rotation, Materiau(), false) {

}

Cylindre::Cylindre(const Cylindre& cylindre) : Cylindre(cylindre.centre, cylindre.hauteur, cylindre.rayon, cylindre.rotation, cylindre.materiau) {

}

Cylindre::~Cylindre() {

}

Cylindre* Cylindre::creerFormeCanonique() {
    /* Cylindre centré à l'origine de rayon 1 et de hauteur 1 */
    return new Cylindre(
        Point(0, 0, 0),
        1,
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
    return centre;
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

bool intersectionPlan(Rayon& r, double& Tin, double& Tout, Point posPlan, Vecteur normPlan) {
    double Dc = r.direction.prodScalaire(normPlan);
    double Dw = Point::creerVecteur(r.origine, posPlan).prodScalaire(normPlan);

    if (Dc == 0) { /* Rayon parrallèle au plan */
        if (Dw > 0) {
            return false;
        }
    } else {
        double t = -Dw / Dc;
        if (Dc >= 0) {
            if (t > Tin && t < Tout) {
                Tout = t;
            }
            if (t < Tin) {
                return false;
            }
        } else {
            if (t > Tin && t < Tout) {
                Tin = t;
            }
            if (t > Tout) {
                return false;
            }
        }
    }

    if (Tin > Tout) {
        return false;
    }
}

bool Cylindre::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
    r.direction = r.direction.unitaire();
    Vecteur v = Vecteur(0, 1, 0);

    Point posPlanInf = Point(0, 0, 0);
    Vecteur normPlanInf = Vecteur(0, -1, 0);
    Point posPlanSup = Point(0, hauteur, 0);
    Vecteur normPlanSup = Vecteur(0, 1, 0);

    Vecteur L = Point::creerVecteur(r.origine, centre);
    Vecteur w = r.direction.prodVectoriel(v);
    double wCarre = w.prodScalaire(w);

    if (wCarre == 0) { /* Cas rayon parrallèle à l'axe du cylindre */
        double a = L.prodScalaire(v);
        Vecteur D = L - a * v;
        double dCarre = D.prodScalaire(D);

        if (dCarre > rayon * rayon) {
            return false;
        }

        return true; /* Intersections à l'infini (dans le cylindre) */

    } else {
        Vecteur wn = w.unitaire();
        double R = std::abs(L.prodScalaire(wn));

        if (R > rayon) {
            return false;
        }

        Vecteur E = L.prodVectoriel(v);
        double t = -E.prodScalaire(wn) / sqrt(wCarre);
        Vecteur F = wn.prodVectoriel(v);
        Vecteur Fn = F.unitaire();
        double s = sqrt(rayon * rayon - R * R) * std::abs(r.direction.prodScalaire(Fn));

        double tin = (t - s);
        double tout = (t + s);
        
        bool haut = intersectionPlan(r, tin, tout, posPlanSup, normPlanSup);

        tin = (t - s);
        tout = (t + s);

        bool bas = intersectionPlan(r, tin, tout, posPlanInf, normPlanInf);

        if (!haut && !bas) {
            intersection = r.origine + tout * r.direction;
        } else {
            return false;
        }

        Vecteur Q = Vecteur(intersection.x, 0, intersection.z);
        Vecteur CP = Point::creerVecteur(centre, intersection);
        double CQ = CP.prodScalaire(v);
        Vecteur QP = CP - CQ * v;
        normale = QP / rayon;

        if (!haut) {
            normale = normPlanSup;
        } else if (!bas) {
            normale = normPlanInf;
        }

        return true;
    }
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