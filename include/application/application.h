#ifndef DEF__APPLICATION
#define DEF__APPLICATION

#include <string>

#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"
#include "../scene/scene.h"
#include "../scene/lumiere.h"
#include "../outils/image.h"
#include "../outils/materiau.h"
#include "../outils/couleur.h"

class Application {
    public:
        Application(int niveau, string fichierOutput, int nbSampling);
        ~Application();

        static void lancerRayons(Scene& scene, Image& image, bool eclairage, int pixelSampling, bool ombrage, bool reflet, bool refraction);
        static void lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, bool eclairage, int pixelSampling, bool ombrage, bool reflet, bool refraction);
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
        int niveau, nbSampling;
        string fichierOutput;

        /**
         * @brief Effectue le lancer de rayon dans la sc�ne donn�. Les fonctionnalit�es d�pendent des param�tres donn�s.
         * @param[in] scene Sc�ne dans laquelle lancer les rayons
         * @param iteration Nombre d'it�ration courante du lancer de rayon, dans le cas du pixel sampling.
         * @param[in] ancienne Image pr�c�demment calcul�e
         * @param[out] nouvelle R�sultat du lanc� de rayons
         * @param pixelSampling Nombre de pixels � lancer dans la sc�ne
         * @param eclairage D�termine s'il faut calculer l'�clairage
         * @param ombrage D�termine s'il faut calculer les ombres
         * @param reflet D�termine s'il faut calculer les reflets.
         * @param refraction D�termine s'il faut calculer la r�fraction.
         * @param f Fonction � appliquer pour le calcul du pixel dans l'image :
         *        Le premier argument Couleur : Le pixel calcul� apr�s un seul lancer de rayon (sans pixel sampling)
         *        Le premier argument int : Le nombre d'it�ration courant
         *        Le deuxieme argument Couleur : L'ancien pixel provenant du param�tre `ancienne`
         *        Renvoie la Couleur du pixel � appliquer
        */
        static void lancerRayonsAux(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle, int pixelSampling, bool eclairage, bool ombrage, bool reflet, bool refraction, Couleur (*f)(Couleur nouveau, int iteration, Couleur ancien));
        static bool interPlusProche(Rayon& r, vector<Forme*>& formes, Intersection& inter);
        static Couleur illuminationFinale(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, bool eclairage, bool ombrage, bool reflet, bool refraction);
        static Couleur illuminations(Intersection& inter, Point& vue, vector<Lumiere>& lumieres, vector<Forme*>& formes, bool ombrage);
        static Couleur illumination(Intersection& inter, Point& vue, Lumiere& lumiere, vector<Forme*>& formes, bool ombrage);
        static bool estIllumine(Point& point, Lumiere& lumiere, vector<Forme*>& formes);
        static Couleur couleurReflechie(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction);
        static Couleur couleurReflechieAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction, unsigned int iteration);
        static Couleur couleurRefracte(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction);
        static Couleur couleurRefracteAux(Intersection& inter, vector<Forme*>& formes, vector<Lumiere>& lumieres, bool eclairage, bool ombrage, bool reflet, bool refraction, unsigned int iteration);
};

#endif