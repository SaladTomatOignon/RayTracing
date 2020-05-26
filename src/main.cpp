#include <iostream>
#include <string>
#include <cxxopts.h>

#include "../../include/application.h"
#include "../../include/scene/scene.h"
#include "../../include/outils/image.h"
#include "../../include/outils/parser.h"

int main(int argc, char *argv[]) {
    Scene scene;
    int niveau = -1, nbSampling = -1;
    string input, output;

    try {
        cxxopts::ParseResult arguments = Parser::parseArguments(argc, argv);

        if (!arguments.count("niveau")) throw invalid_argument("Le niveau de rendu doit être renseigné");
        if (!arguments.count("input")) throw invalid_argument("Le fichier de configuration json doit être renseigné");
        if (!arguments.count("output")) throw invalid_argument("Le nom du fichier image de sortie doit être renseigné");

        niveau = arguments["niveau"].as<int>();
        input = arguments["input"].as<string>();
        output = arguments["output"].as<string>();

        if (arguments.count("ps")) {
            nbSampling = arguments["ps"].as<int>();
        } else if (niveau == 3) {
            throw invalid_argument("Le nombre de rayon par pixel (valeur du pixel sampling) doit être renseigné pour le niveau 3");
        }
    } catch (exception e) {
        cerr << "Erreur durant le parsing des arguments : " << e.what() << endl;
        return EXIT_FAILURE;
    }

    Application application(niveau, output, nbSampling);

    try {
        scene = Parser::parseJSON(input);
    } catch (logic_error le) {
        cerr << "Erreur durant le parsing du fichier de configuration : " << le.what() << endl;
        return EXIT_FAILURE;
    }

    if (niveau == 1 || niveau == 3) {
        application.enregistrerImage(scene);
    } else if (niveau == 2) {
        application.visualiserScene(scene);
    }

    return EXIT_SUCCESS;
}