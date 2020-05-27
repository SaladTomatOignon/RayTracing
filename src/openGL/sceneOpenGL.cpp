#include "../../include/openGL/sceneOpenGL.h"
#include "../../include/openGL/input.h"
#include "../../include/outils/image.h"
#include "../../include/scene/scene.h"
#include "../../include/application.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;

SceneOpenGL::SceneOpenGL(string titreFenetre, int largeurFenetre, int hauteurFenetre, Scene scene, string fichierOutput, int nbSampling) {
    m_titreFenetre = titreFenetre;
    m_largeurFenetre = largeurFenetre;
    m_hauteurFenetre = hauteurFenetre;
    m_fenetre = nullptr;
    m_contexteOpenGL = nullptr;
    m_scene = Scene(scene);
    m_input = Input();
    m_fichierOutput = fichierOutput;
    m_nbSampling = nbSampling;
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


    // Cr�ation de la fen�tre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if (m_fenetre == 0) {
        cerr << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();

        return false;
    }


    // Cr�ation du contexte OpenGL
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


        // Si l'initialisation a �chou� :
        if (initialisationGLEW != GLEW_OK) {
            // On affiche l'erreur gr�ce � la fonction : glewGetErrorString(GLenum code)
            cerr << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << endl;

            // On quitte la SDL
            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif

    // Tout s'est bien pass�, on retourne true
    return true;
}

void SceneOpenGL::bouclePrincipale() {
    /* Avec le lancer de rayons progressifs, le rendu final se base sur un rendu initial, on a donc besoin de 2 images */
    Image rendu1(m_scene.grille.resolution_l, m_scene.grille.resolution_h);
    Image rendu2(m_scene.grille.resolution_l, m_scene.grille.resolution_h);
    unsigned int iterations = 1;

    // Variables relatives à la boucle
    bool terminer = false;
    bool renduProgressif = true;
    unsigned int frameRate(1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    Application::lancerRayons(m_scene, rendu1, true, m_nbSampling);

    // Boucle principale
    while (!m_input.terminer()) {
        // On d�finit le temps de d�but de boucle
        debutBoucle = SDL_GetTicks();

        /* --------------------------------------------------------------- */
        /* ---------------------- GESTION DE LA LOGIQUE ------------------ */
        /* --------------------------------------------------------------- */

        Application::lancerRayonsProgressifs(m_scene, iterations, rendu1, rendu2, m_nbSampling);

        // Gestion des évènements
        m_input.updateEvenements();

        if (m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;

        if (m_input.getTouche(SDL_SCANCODE_RETURN)) {
            rendu2.exportPPM(m_fichierOutput.c_str());
        }

        if (m_input.getTouche(SDL_SCANCODE_P)) {
            renduProgressif = !renduProgressif;
            if (renduProgressif) {
                cout << "Rendu progressif activé" << endl;
            } else {
                cout << "Rendu progressif désactivé" << endl;
            }
        }

        /* Pour forcer l'�valuation des 2 m�thodes... */
        bool deplacer = deplacerCamera();
        bool orienter = orienterCamera();
        if (deplacer || orienter) {
            iterations = 1;
        } else {
            if (renduProgressif) {
                iterations++;
            }
        }

        rendu1 = rendu2;

        /* --------------------------------------------------------------- */
        /* ---------------------- AFFICHAGE DE L'ECRAN ------------------- */
        /* --------------------------------------------------------------- */

        // Nettoyage de l'�cran
        glClear(GL_COLOR_BUFFER_BIT);

        afficherImage(rendu2);

        // Actualisation de la fen�tre
        SDL_GL_SwapWindow(m_fenetre);

        // Calcul du temps �coul�
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;

        // Si n�cessaire, on met en pause le programme
        if (tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }

}

void SceneOpenGL::afficherImage(Image& image) {
    int nbPixels = image.largeur * image.hauteur * 3;
    unsigned char* window_RGBData = new unsigned char[nbPixels]();

    for (unsigned int i = 0; i < image.hauteur; i++) {
        for (unsigned int j = 0; j < image.largeur; j++) {
            window_RGBData[3 * (i * image.largeur + j) + 0] = image[image.hauteur - 1 - i][j].r;
            window_RGBData[3 * (i * image.largeur + j) + 1] = image[image.hauteur - 1 - i][j].g;
            window_RGBData[3 * (i * image.largeur + j) + 2] = image[image.hauteur - 1 - i][j].b;
        }
    }

    glDrawPixels(image.largeur, image.hauteur, GL_RGB, GL_UNSIGNED_BYTE, window_RGBData);

    delete [] window_RGBData;
}

bool SceneOpenGL::deplacerCamera() {
    bool deplacer = false;

    /* ATTENTION : SDL ne consid�re que les clavier QWERTY */

    if (m_input.getTouche(SDL_SCANCODE_Q)) {
        m_scene.camera.translater(Camera::DIRECTION::DERRIERE);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_E)) {
        m_scene.camera.translater(Camera::DIRECTION::DEVANT);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_A)) {
        m_scene.camera.translater(Camera::DIRECTION::GAUCHE);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_W)) {
        m_scene.camera.translater(Camera::DIRECTION::HAUT);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_D)) {
        m_scene.camera.translater(Camera::DIRECTION::DROITE);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_S)) {
        m_scene.camera.translater(Camera::DIRECTION::BAS);
        deplacer = true;
    }

    if (deplacer) {
        m_scene.grille.positionner(m_scene.camera);
        return true;
    }

    return false;
}

bool SceneOpenGL::orienterCamera() {
    bool deplacer = false;

    if (m_input.getTouche(SDL_SCANCODE_LEFT)) {
        m_scene.camera.orienter(Camera::DIRECTION::GAUCHE);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_UP)) {
        m_scene.camera.orienter(Camera::DIRECTION::HAUT);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_RIGHT)) {
        m_scene.camera.orienter(Camera::DIRECTION::DROITE);
        deplacer = true;
    }

    if (m_input.getTouche(SDL_SCANCODE_DOWN)) {
        m_scene.camera.orienter(Camera::DIRECTION::BAS);
        deplacer = true;
    }

    if (deplacer) {
        Vecteur vecteurVertical = Vecteur(0, 1, 0);
        m_scene.grille.inclinaison_h = -1 * m_scene.camera.orientation.prodVectoriel(vecteurVertical);
        m_scene.grille.positionner(m_scene.camera);
        return true;
    }

    return false;
}