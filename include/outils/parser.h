#ifndef DEF__PARSER
#define DEF__PARSER

#include <vector>
#include <string>
#include "../rapidjson/document.h"
#include "../scene/scene.h"
#include "../scene/camera.h"
#include "../scene/grille.h"
#include "../scene/sphere.h"
#include "../scene/rectangle.h"
#include "../scene/triangle.h"
#include "../scene/cylindre.h"
#include "../scene/lumiere.h"
#include "../outils/couleur.h"
#include "../outils/materiau.h"

using namespace rapidjson;

class Parser {
    public:
        Parser();
        ~Parser();

        /*!
         * \brief Cr�e une sc�ne � partir d'un fichier json.
         *
         * \param fileName Fichier au format json � ouvrir et parser
         *
         * \return La sc�ne pars�e
         */
        static Scene parseJSON(string fileName);

    private:
        enum class TypeForme {
            SPHERE,
            RECTANGLE,
            TRIANGLE,
            CYLINDRE,
            NONE
        };

        static Camera parseCamera(Document& jsonObject);
        static Grille parseGrille(Document& jsonObject);
        static vector<Forme*> parseFormes(Document& jsonObject);
        static vector<Lumiere> parseLumieres(Document& jsonObject);
        static Lumiere parseLumiere(Value& forme);
        static TypeForme getTypeForme(string forme);
        static Forme* parseForme(Value& forme);
        static Point getPoint(Value& forme, const char* champ);
        static Materiau getMateriau(Value& forme);
        static Couleur getCouleur(Value& forme);
        static Sphere* parseSphere(Value& forme);
        static Rectangle* parseRectangle(Value& forme);
        static Triangle* parseTriangle(Value& forme);
        static Cylindre* parseCylindre(Value& forme);
};

#endif