#include <iostream>
#include <string>
#include <time.h>
#include <math.h>

#include "../../include/application/application.h"
#include "../../include/application/context.h"
#include "../../include/scene/scene.h"
#include "../../include/outils/image.h"
#include "../../include/outils/parser.h"
#include "../../include/outils/cxxopts.h"

void initParametres(Context& parametres) {
    srand(time(NULL));

    parametres.maxRecursionsReflexion = 16;
    parametres.maxRecursionsRefraction = 16;
    parametres.nbThreads = 8;

    switch (parametres.niveau) {
        /* Les niveaux plus élevés héritent des fonctionnalités des niveaux plus bas */
        case 3:
            parametres.ombrageActive = true;
            parametres.reflexionActive = true;
            parametres.transparenceActive = true;
        case 2:
            parametres.eclairageActive = true;
        case 1:
            /* Rien à activer pour le niveau 1 */
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    Scene scene;
    Context parametres;
    string input;
    bool renduDynamique;
    
    try {
        cxxopts::ParseResult arguments = Parser::parseArguments(argc, argv);

        if (!arguments.count("niveau")) throw invalid_argument("Le niveau de rendu doit être renseigné");
        if (!arguments.count("input")) throw invalid_argument("Le fichier de configuration json doit être renseigné");
        if (!arguments.count("output")) throw invalid_argument("Le nom du fichier image de sortie doit être renseigné");

        parametres.niveau = arguments["niveau"].as<int>();
        input = arguments["input"].as<string>();
        parametres.fichierSortie = arguments["output"].as<string>();
        renduDynamique = parametres.niveau == 2 || arguments.count("force");

        if (arguments.count("ps")) {
            parametres.sampling = arguments["ps"].as<int>();
        } else if (parametres.niveau == 3) {
            throw invalid_argument("Le nombre de rayon par pixel (valeur du pixel sampling) doit être renseigné pour le niveau 3");
        }
    } catch (invalid_argument e) {
        cerr << "Erreur durant le parsing des arguments : " << e.what() << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Erreur durant le parsing des arguments. Utilisez 'lray --help'" << endl;
        return EXIT_FAILURE;
    }

    initParametres(parametres);
    Application application(parametres);

    try {
        scene = Parser::parseJSON(input);
    } catch (logic_error le) {
        cerr << "Erreur durant le parsing du fichier de configuration : " << le.what() << endl;
        return EXIT_FAILURE;
    }

    if (renduDynamique) {
        application.visualiserScene(scene);
    } else {
        application.enregistrerImage(scene);
    }

    return EXIT_SUCCESS;
}