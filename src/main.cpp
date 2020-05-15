#include <iostream>

#include "../../include/scene/scene.h"
#include "../../include/outils/parser.h"

int main(int argc, char *argv[]) {
    Scene scene;

    try {
        scene = Parser::parseJSON(string(argv[1]));
    } catch (logic_error le) {
        cerr << "Erreur durant le parsing du fichier de configuration : " << le.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}