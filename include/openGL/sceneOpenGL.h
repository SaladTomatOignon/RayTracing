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
        SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, Scene scene, string fichierOutput, bool eclairage, int nbSampling, bool ombrage, bool reflet);
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

        /* Objet Input pour la gestion des évènements */
        Input m_input;
        /* True s'il faut calculer l'éclairage, False sinon */
        bool m_eclairage;
        /* Nombre de rayons lancés par pixel */
        int m_nbSampling;
        /* True s'il faut calculer les ombres, False sinon */
        bool m_ombrage;
        /* True s'il faut calculer les reflets et la transparence, False sinon */
        bool m_reflet;

        Scene m_scene;
        string m_fichierOutput;

        void afficherImage(Image& image);
        bool deplacerCamera();
        bool orienterCamera();
};

#endif