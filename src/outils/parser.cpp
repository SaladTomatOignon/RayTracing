#include "../../include/outils/parser.h"
#include "../../include/rapidjson/document.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
using namespace rapidjson;

Parser::Parser() {

}

Parser::~Parser() {

}

Scene Parser::parseJSON(string const fileName) {
    /* Lecture du contenu du fichier dans une seule string. */
    ifstream file(fileName);

    if (!file) {
        throw logic_error("Le fichier " + fileName + " est introuvable");
    }

    string json((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

    /* Parsing du fichier json par rapidJson. */
    Document document;
    ParseResult resultat = document.Parse(json.c_str());

    if (!resultat) {
        throw logic_error("Le fichier n'est pas conforme au format JSON");
    }

    /* Parsing des �l�ments composant la sc�ne. */
    Camera camera = parseCamera(document);
    vector<Forme*> formes = parseFormes(document);

    return Scene(camera, formes);
}

Camera Parser::parseCamera(Document& jsonObject) {
    /* Recuperation de la position de la cam�ra */
    Point camera_position;
    if (!jsonObject.HasMember("camera_position") || !jsonObject["camera_position"].IsArray() || jsonObject["camera_position"].GetArray().Size() != 3) {
        throw logic_error("Position de la cam�ra manquante ou invalide");
    }
    else {
        const Value& coords = jsonObject["camera_position"];
        camera_position = Point(coords[0].GetDouble(), coords[1].GetDouble(), coords[2].GetDouble());
    }

    /* Recuperation de l'orientation de la cam�ra */
    Vecteur camera_orientation;
    if (!jsonObject.HasMember("camera_orientation") || !jsonObject["camera_orientation"].IsArray() || jsonObject["camera_orientation"].GetArray().Size() != 3) {
        throw logic_error("Orientation de la cam�ra manquante ou invalide");
    }
    else {
        const Value& coords = jsonObject["camera_orientation"];
        camera_orientation = Vecteur(coords[0].GetDouble(), coords[1].GetDouble(), coords[2].GetDouble());
    }

    return Camera(camera_position, camera_orientation);
}

vector<Forme*> Parser::parseFormes(Document& jsonObject) {
    vector<Forme*> formes;

    if (jsonObject.HasMember("formes")) {
        if (!jsonObject["formes"].IsArray()) {
            throw logic_error("Les formes doivent �tre repr�sent�es sous forme d'un tableau d'objets JSON");
        }

        for (auto& forme : jsonObject["formes"].GetArray()) {
            formes.push_back(parseForme(forme));
        }
    }

    return formes;
}

Parser::TypeForme Parser::getTypeForme(string forme) {
    string formeToUpperCase = string(forme);
    transform(formeToUpperCase.begin(), formeToUpperCase.end(), formeToUpperCase.begin(), ::toupper);

    if (formeToUpperCase == "SPHERE") {
        return TypeForme::SPHERE;
    }

    if (formeToUpperCase == "RECTANGLE") {
        return TypeForme::RECTANGLE;
    }

    if (formeToUpperCase == "TRIANGLE") {
        return TypeForme::TRIANGLE;
    }
}

Forme* Parser::parseForme(Value& forme) {
    if (!forme.HasMember("type") || !forme["type"].IsString()) {
        throw logic_error("Vous devez sp�cifier le type de la forme pour chaque forme");
    } else {
        TypeForme type = getTypeForme(string(forme["type"].GetString()));

        switch (type) {
            case TypeForme::SPHERE:
                return parseSphere(forme);
                break;
            case TypeForme::RECTANGLE:
                return parseRectangle(forme);
                break;
            case TypeForme::TRIANGLE:
                return parseTriangle(forme);
                break;
            default:
                break;
        }
    }
}

Point Parser::getPoint(Value& forme, const char* champ) {
    Point point;

    if (!forme.HasMember(champ) || !forme[champ].IsArray() || forme[champ].GetArray().Size() != 3) {
        throw logic_error("");
    } else {
        const Value& coords = forme[champ];
        point = Point(coords[0].GetDouble(), coords[1].GetDouble(), coords[2].GetDouble());
    }

    return point;
}

Sphere* Parser::parseSphere(Value& forme) {
    /* R�cup�ration du centre de la sph�re. */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Position de la sph�re manquante ou invalide.");
    }

    /* R�cup�ration du rayon de la sph�re. */
    double rayon;
    if (!forme.HasMember("rayon")) {
        throw logic_error("Rayon de la sph�re manquant.");
    } else {
        rayon = forme["rayon"].GetDouble();
    }

    return new Sphere(centre, rayon);
}

Rectangle* Parser::parseRectangle(Value& forme) {
    /* D�termination du point A */
    Point pointA;
    try {
        pointA = getPoint(forme, "pointA");
    } catch (logic_error le) {
        throw logic_error("Point A du rectangle manquant ou invalide.");
    }

    /* D�termination du point B */
    Point pointB;
    try {
        pointB = getPoint(forme, "pointB");
    } catch (logic_error le) {
        throw logic_error("Point B du rectangle manquant ou invalide.");
    }

    /* D�termination du point C */
    Point pointC;
    try {
        pointC = getPoint(forme, "pointC");
    } catch (logic_error le) {
        throw logic_error("Point C du rectangle manquant ou invalide.");
    }

    /* D�termination du point D */
    Point pointD;
    try {
        pointD = getPoint(forme, "pointD");
    } catch (logic_error le) {
        throw logic_error("Point D du rectangle manquant ou invalide.");
    }

    return new Rectangle(pointA, pointB, pointC, pointD);
}

Triangle* Parser::parseTriangle(Value& forme) {
    /* D�termination du point A */
    Point pointA;
    try {
        pointA = getPoint(forme, "pointA");
    } catch (logic_error le) {
        throw logic_error("Point A du triangle manquant ou invalide.");
    }

    /* D�termination du point B */
    Point pointB;
    try {
        pointB = getPoint(forme, "pointB");
    } catch (logic_error le) {
        throw logic_error("Point B du triangle manquant ou invalide.");
    }

    /* D�termination du point C */
    Point pointC;
    try {
        pointC = getPoint(forme, "pointC");
    } catch (logic_error le) {
        throw logic_error("Point C du triangle manquant ou invalide.");
    }

    return new Triangle(pointA, pointB, pointC);
}
