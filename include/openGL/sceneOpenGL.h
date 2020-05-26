#ifndef DEF_SCENE_OPENGL
#define DEF_SCENE_OPENGL

#ifdef WIN32
    #include <GL/glew.h>
#else
    #define GL3_PROTOTYPES 1
    #include <GL/glut.h>
#endif

#include "../scene/scene.h"
#include "../outils/image.h"
#include "../openGL/input.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class SceneOpenGL {
    public:
        SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Scene scene, string fichierOutput);
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

        // Objet Input pour la gestion des �v�nements
        Input m_input;

        Scene m_scene;
        string m_fichierOutput;

        void afficherImage(Image& image);
        bool deplacerCamera();
        bool orienterCamera();
};

#endif