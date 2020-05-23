#include "../../include/openGL/sceneOpenGL.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) {
    m_titreFenetre = titreFenetre;
    m_largeurFenetre = largeurFenetre;
    m_hauteurFenetre = hauteurFenetre;
    m_fenetre = nullptr;
    m_contexteOpenGL = nullptr;
}

SceneOpenGL::~SceneOpenGL() {
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();

        return false;
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (m_fenetre == 0) {
        cerr << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL
    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if (m_contexteOpenGL == 0) {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL() {
    #ifdef WIN32

        // On initialise GLEW
        GLenum initialisationGLEW(glewInit());


        // Si l'initialisation a échoué :
        if (initialisationGLEW != GLEW_OK) {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
            cerr << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << endl;

            // On quitte la SDL
            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif

    // Tout s'est bien passé, on retourne true
    return true;
}

void SceneOpenGL::bouclePrincipale() {
    // Variables
    bool terminer(false);

    // Boucle principale
    while (!terminer) {
        // Gestion des évènements
        SDL_WaitEvent(&m_evenements);

        if (m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = true;

        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT);

        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);
    }
}