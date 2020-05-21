#ifndef DEF__PARSER
#define DEF__PARSER

#include <iostream>
#include <vector>
#include "../rapidjson/document.h"
#include "../scene/scene.h"
#include "../scene/camera.h"
#include "../scene/grille.h"
#include "../scene/sphere.h"
#include "../scene/rectangle.h"
#include "../scene/triangle.h"

using namespace std;
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
            NONE
        };

        static Camera parseCamera(Document& jsonObject);
        static Grille parseGrille(Document& jsonObject);
        static vector<Forme*> parseFormes(Document& jsonObject);
        static TypeForme getTypeForme(string forme);
        static Forme* parseForme(Value& forme);
        static Point getPoint(Value& forme, const char* champ);
        static Sphere* parseSphere(Value& forme);
        static Rectangle* parseRectangle(Value& forme);
        static Triangle* parseTriangle(Value& forme);
};

#endif