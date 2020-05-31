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

        static void lancerRayonsAux(Scene* scene, unsigned int iteration, Image& ancienne, Image* nouvelle, Context& parametres, Couleur(*f)(Couleur nouveau, int iteration, Couleur ancien));
        /**
         * @brief Effectue le lancer de rayon dans la sc�ne donn�. Les fonctionnalit�es d�pendent des param�tres donn�s.
         * @param[in] scene Sc�ne dans laquelle lancer les rayons
         * @param iteration Nombre d'it�ration courante du lancer de rayon, dans le cas du pixel sampling.
         * @param[in] ancienne Image pr�c�demment calcul�e
         * @param[out] nouvelle R�sultat du lanc� de rayons
         * @param parametres Param�tres de la sc�ne
         * @param f Fonction � appliquer pour le calcul du pixel dans l'image :
         *        Le premier argument Couleur : Le pixel calcul� apr�s un seul lancer de rayon (sans pixel sampling)
         *        Le premier argument int : Le nombre d'it�ration courant
         *        Le deuxieme argument Couleur : L'ancien pixel provenant du param�tre `ancienne`
         *        Renvoie la Couleur du pixel � appliquer
         * @param debutLigne La premi�re ligne de l'image � calculer (en partant du haut de l'image).
         * @param finLigne La derni�re ligne de l'image � calculer (en partant du haut de l'image).
        */
        static void lancerRayonsParLignes(Scene** scene, unsigned int iteration, Image& ancienne, Image** nouvelle, Context& parametres, Couleur (*f)(Couleur nouveau, int iteration, Couleur ancien), unsigned debutLigne, unsigned finLigne);
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