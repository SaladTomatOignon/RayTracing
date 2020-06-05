#ifndef DEF__PARSER
#define DEF__PARSER

#include <vector>
#include <string>

#include "../geometrie/vecteur.h"
#include "../rapidjson/document.h"
#include "../scene/scene.h"
#include "../scene/camera.h"
#include "../scene/grille.h"
#include "../scene/sphere.h"
#include "../scene/rectangle.h"
#include "../scene/triangle.h"
#include "../scene/cylindre.h"
#include "../scene/ellipsoide.h"
#include "../scene/cube.h"
#include "../scene/paveDroit.h"
#include "../scene/plan.h"
#include "../scene/cone.h"
#include "../scene/lumiere.h"
#include "../outils/couleur.h"
#include "../outils/materiau.h"
#include "../outils/cxxopts.h"

using namespace rapidjson;

class Parser {
    public:
        Parser();
        ~Parser();

        /*!
         * \brief Crée une scène à partir d'un fichier json.
         *
         * \param fileName Fichier au format json à ouvrir et parser
         *
         * \return La scène parsée
         */
        static Scene parseJSON(string fileName);

        /* Parsing de la ligne de commande */
        static cxxopts::ParseResult parseArguments(int argc, char* argv[]);

    private:
        enum class TypeForme {
            SPHERE,
            RECTANGLE,
            TRIANGLE,
            CYLINDRE,
            PLAN,
            ELLIPSOIDE,
            CUBE,
            PAVE_DROIT,
            CONE,
            NONE
        };

        /* Parsing du fichier de configuration Json */
        static Camera parseCamera(Document& jsonObject);
        static Grille parseGrille(Document& jsonObject);
        static vector<Forme*> parseFormes(Document& jsonObject);
        static vector<Lumiere> parseLumieres(Document& jsonObject);
        static Lumiere parseLumiere(Value& forme);
        static TypeForme getTypeForme(string forme);
        static Forme* parseForme(Value& forme);
        static Point getPoint(Value& forme, const char* champ);
        static Vecteur getRotation(Value& forme);
        static Materiau getMateriau(Value& forme);
        static Couleur getCouleur(Value& forme);
        static Couleur getSpecularite(Value& forme);
        static Sphere* parseSphere(Value& forme);
        static Rectangle* parseRectangle(Value& forme);
        static Triangle* parseTriangle(Value& forme);
        static Cylindre* parseCylindre(Value& forme);
        static Cone* parseCone(Value& forme);
        static Ellipsoide* parseEllipsoide(Value& forme);
        static Cube* parseCube(Value& forme);
        static PaveDroit* parsePaveDroit(Value& forme);
        static Plan* parsePlan(Value& forme);
};

#endif