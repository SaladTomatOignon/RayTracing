#ifndef DEF__SCENE
#define DEF__SCENE

#include "../scene/camera.h"
#include "../scene/forme.h"
#include <vector>

using namespace std;

class Scene {
    public:
        Scene();
        Scene(Camera camera, vector<Forme*> formes);
        ~Scene();

    private:
        Camera camera;
        vector<Forme*> formes;
    };

#endif