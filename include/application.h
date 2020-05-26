#ifndef DEF__APPLICATION
#define DEF__APPLICATION

#include <string>

#include "../geometrie/point.h"
#include "../geometrie/vecteur.h"
#include "../scene/scene.h"
#include "../scene/lumiere.h"
#include "../outils/image.h"
#include "../outils/materiau.h"

class Application {
    public:
        Application(int niveau, string fichierOutput, int nbSampling);
        ~Application();

        static void lancerRayons(Scene& scene, Image& image, bool eclairage);
        static void lancerRayonsProgressifs(Scene& scene, unsigned int iteration, Image& ancienne, Image& nouvelle);
        void visualiserScene(Scene& scene);
        void enregistrerImage(Scene& scene);

        struct Intersection {
            Materiau materiau;
            Point intersection;
            Vecteur normale;
        };

    private:
        int niveau, nbSampling;
        string fichierOutput;

        static bool interPlusProche(Rayon r, vector<Forme*> formes, Intersection& inter);
        static Couleur illumination(Intersection inter, Point camera, Lumiere lumiere);
};

#endif