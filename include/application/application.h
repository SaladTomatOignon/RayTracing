#ifndef DEF__APPLICATION
#define DEF__APPLICATION

#include <string>

#include "../application/context.h"
#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"
#include "../scene/scene.h"
#include "../scene/lumiere.h"
#include "../outils/image.h"
#include "../outils/materiau.h"
#include "../outils/couleur.h"

class Application {
    public:
        Application(Context& parametres);
        ~Application();

        static void lancerRayons(Scene& scene, Image& image, Context& parametres);
        static void lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, Context& parametres);
        void visualiserScene(Scene& scene);
        void enregistrerImage(Scene& scene);

        struct Intersection {
            Materiau materiau;
            Point intersection;
            Vecteur normale;
            Rayon incident;
            bool forme2D;
        };

    private:
        Context parametres;

        /**
         * @brief Effectue le lancer de rayon dans la scène donné. Les fonctionnalitées dépendent des paramètres donnés.
         * @param[in] scene Scène dans laquelle lancer les rayons
         * @param iteration Nombre d'itération courante du lancer de rayon, dans le cas du pixel sampling.
         * @param[in] ancienne Image précédemment calculée
         * @param[out] nouvelle Résultat du lancé de rayons
         * @param pixelSampling Nombre de pixels à lancer dans la scène
         * @param eclairage Détermine s'il faut calculer l'éclairage
         * @param ombrage Détermine s'il faut calculer les ombres
         * @param reflet Détermine s'il faut calculer les reflets.
         * @param refraction Détermine s'il faut calculer la réfraction.
         * @param f Fonction à appliquer pour le calcul du pixel dans l'image :
         *        Le premier argument Couleur : Le pixel calculé après un seul lancer de rayon (sans pixel sampling)
         *        Le premier argument int : Le nombre d'itération courant
         *        Le deuxieme argument Couleur : L'ancien pixel provenant du paramètre `ancienne`
         *        Renvoie la Couleur du pixel à appliquer
        */
        static void lancerRayonsAux(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, Context& parametres, Couleur (*f)(Couleur nouveau, int iteration, Couleur ancien));
        static bool interPlusProche(Rayon& r, vector<Forme*>& formes, Intersection& inter);
        static Couleur illuminationFinale(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, Context& parametres);
        static Couleur illuminations(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, Context& parametres);
        static Couleur illumination(Intersection& inter, Point& vue, Lumiere& lumiere, vector<Forme*>& formes, Context& parametres);
        static bool estIllumine(Point& point, Lumiere& lumiere, vector<Forme*>& formes);
        static Couleur couleurReflechie(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, Context& parametres);
        static Couleur couleurReflechieAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, Context& parametres, unsigned int iteration);
        static Couleur couleurRefracte(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, Context& parametres);
        static Couleur couleurRefracteAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, Context& parametres, unsigned int iteration);
};

#endif