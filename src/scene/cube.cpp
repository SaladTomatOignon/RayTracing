#include "../../include/scene/cube.h"
#include "../../include/outils/couleur.h"
#include "../../include/geometrie/point.h"
#include "../../include/geometrie/matrice.h"
#include "../../include/geometrie/rayon.h"
#include <math.h>
#include <algorithm>

using namespace std;

Cube::Cube(Point centre, double taille, Vecteur rotation, Materiau materiau, bool estCanonique) : Forme(centre, rotation, materiau) {
	this->taille = taille;

	if (!estCanonique) {
		initialiserMatricesTransformation();
	}
}

Cube::Cube(Point centre, double taille, Vecteur rotation, Materiau materiau) : Cube(centre, taille, rotation, materiau, false) {

}

Cube::Cube(Point centre, double taille, Vecteur rotation) : Cube(centre, taille, rotation, Materiau(), false) {

}

Cube::Cube(const Cube& cube) : Cube(cube.centre, cube.taille, cube.rotation, cube.materiau) {

}

Cube::~Cube() {

}

Cube* Cube::creerFormeCanonique() {
    // Cube centré en (0, 0, 0) de longueur 2
    return new Cube(Point(0, 0, 0), 2, Vecteur(), Materiau(), true);
}

Cube* Cube::getFormeCanonique() {
    return (Cube*)formeCanonique;
}

Point Cube::getCentre() {
    return Point(centre);
}

void Cube::homothetieFormeCanonique() {
	Md = Md * Matrice::mat_homothetie(taille / 2, taille / 2, taille / 2);
	Mi = Matrice::mat_homothetie(1 / (taille / 2), 1 / (taille / 2), 1 / (taille / 2)) * Mi;
	Mn = Mn * Matrice::mat_homothetie((taille / 2) * (taille / 2), (taille / 2) * (taille / 2), (taille / 2) * (taille / 2));
}

void Cube::rotationFormeCanonique() {
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

void Cube::translationFormeCanonique() {
	Md = Md * Matrice::mat_translation(centre.x, centre.y, centre.z);
	Mi = Matrice::mat_translation(-centre.x, -centre.y, -centre.z) * Mi;
	Mn = Mn * Matrice::mat_translation(centre.x, centre.y, centre.z);
}

bool Cube::intersectionCanonique(Rayon& r, Point& intersection, Vecteur& normale) {
	Vecteur u = r.direction.unitaire();
	static Vecteur C[6] = { {1., 0., 0.}, {-1, 0, 0}, {0., 1., 0.}, {0., -1., 0.}, {0., 0., 1.}, {0., 0., -1.} };
	bool flag[6] = { 0, 0, 0, 0, 0, 0 };
	int i;
	double ps, t;
	Vecteur AC;
	Point J;

	/* Faces "visibles" par le rayon */
	/* flag[i] = true <=> Face potentiellement visible */
	if (r.origine.x > 1.) {
		flag[0] = true;
	} else if (r.origine.x < -1) {
		flag[1] = true;
	}

	if (r.origine.y > 1.) {
		flag[2] = true;
	} else if (r.origine.y < -1) {
		flag[3] = true;
	}

	if (r.origine.z > 1.) {
		flag[4] = true;
	} else if (r.origine.z < -1) {
		flag[5] = true;
	}

	for (i = 0; i < 6; i++) {
		if (flag[i] == false) {
			continue;
		}

		ps = u.prodScalaire(C[i]);

		if (ps >= 0.) {
			continue;
		}

		AC.x = C[i].x - r.origine.x;
		AC.y = C[i].y - r.origine.y;
		AC.z = C[i].z - r.origine.z;

		t = AC.prodScalaire(C[i]) / ps;

		/* J = A + t*vect(u) */
		J.x = r.origine.x + t * u.x;
		J.y = r.origine.y + t * u.y;
		J.z = r.origine.z + t * u.z;

		/* Vérification que Point J est bien DANS la facette */
		if (max(abs(J.x), max(abs(J.y), abs(J.z))) > 1 + _EPSILON_) {
			continue;
		}

		/* On a trouvé le bon point */
		intersection = J;
		normale = C[i];

		return true;
	}

	return false;
}

bool Cube::intersection(Rayon& r, Point& intersection, Vecteur& normale) {
	Rayon rCanonique = Rayon(Mi * r.origine, Mi * r.direction);

	if (!intersectionCanonique(rCanonique, intersection, normale)) {
		return false;
	}

	intersection = Point(Md * intersection);
	normale = Mn * normale;
	normale = normale.unitaire();

	return true;
}