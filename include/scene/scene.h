#ifndef DEF__SCENE
#define DEF__SCENE

#include "../scene/camera.h"
#include "../scene/grille.h"
#include "../scene/forme.h"
#include <vector>

using namespace std;

class Scene {
    public:
        Scene();
        Scene(Camera camera, Grille grille, vector<Forme*> formes);
        Scene(const Scene& scene);
        ~Scene();

        Camera camera;
        Grille grille;
        vector<Forme*> formes;
    };

#endif