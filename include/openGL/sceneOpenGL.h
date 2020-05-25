#ifndef DEF_SCENE_OPENGL
#define DEF_SCENE_OPENGL

#ifdef WIN32
    #include <GL/glew.h>
#else
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>
#endif

#include "../scene/scene.h"
#include "../outils/image.h"
#include "../openGL/input.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class SceneOpenGL {
    public:
        SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Scene scene);
        ~SceneOpenGL();

        bool initialiserFenetre();
        bool initGL();
        void bouclePrincipale();

    private:
        std::string m_titreFenetre;
        int m_largeurFenetre;
        int m_hauteurFenetre;

        SDL_Window* m_fenetre;
        SDL_GLContext m_contexteOpenGL;
        SDL_Event m_evenements;

        // Objet Input pour la gestion des évènements
        Input m_input;

        Scene m_scene;

        void afficherImage(Image& image);
        void deplacerCamera();
        void orienterCamera();
};

#endif