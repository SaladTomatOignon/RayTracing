#include "../../geometrie/point.h"
#include "../../geometrie/vecteur.h"
#include "../../include/outils/parser.h"
#include "../../include/outils/couleur.h"
#include "../../include/rapidjson/document.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/camera.h"
#include "../../include/scene/grille.h"
#include "../../include/scene/rectangle.h"
#include "../../include/scene/sphere.h"
#include "../../include/scene/triangle.h"
#include "../../include/scene/cylindre.h"
#include "../../include/scene/ellipsoide.h"
#include "../../include/scene/cube.h"
#include "../../include/scene/plan.h"
#include "../../include/scene/cone.h"
#include "../../include/scene/lumiere.h"

#include <fstream>
#include <algorithm>
#include <string>
#include <cxxopts.h>

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
    Grille grille = parseGrille(document);
    vector<Forme*> formes = parseFormes(document);
    vector<Lumiere> lumieres = parseLumieres(document);
    Scene scene(camera, grille, formes, lumieres);

    /* Libération des formes parsées allouées */
    for (const auto* forme : formes) {
        delete forme;
    }

    return scene;
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

Grille Parser::parseGrille(Document& jsonObject) {
    /* R�cup�ration de la distance focale. */
    double distanceFocale;
    if (!jsonObject.HasMember("distance_focale")) {
        throw logic_error("Distance focale de la caméra manquante.");
    } else {
        distanceFocale = jsonObject["distance_focale"].GetDouble();
    }

    /* R�cup�ration de la taille en largeur de la grille. */
    double definitionLargeur;
    if (!jsonObject.HasMember("definition_largeur")) {
        throw logic_error("Taille en largeur de la grille manquante.");
    } else {
        definitionLargeur = jsonObject["definition_largeur"].GetDouble();
    }

    /* R�cup�ration de la taille en hauteur de la grille. */
    double definitionHauteur;
    if (!jsonObject.HasMember("definition_hauteur")) {
        throw logic_error("Taille en hauteur de la grille manquante.");
    } else {
        definitionHauteur = jsonObject["definition_hauteur"].GetDouble();
    }

    /* R�cup�ration de la resolution en largeur de la grille. */
    unsigned int resolutionLargeur;
    if (!jsonObject.HasMember("resolution_largeur")) {
        throw logic_error("Resolution en largeur de la grille manquante.");
    } else {
        resolutionLargeur = jsonObject["resolution_largeur"].GetInt();
    }

    /* R�cup�ration de la resolution en hauteur de la grille. */
    unsigned int resolutionHauteur;
    if (!jsonObject.HasMember("resolution_hauteur")) {
        throw logic_error("Resolution en hauteur de la grille manquante.");
    } else {
        resolutionHauteur = jsonObject["resolution_hauteur"].GetInt();
    }

    /* Recuperation de l'inclinaison de la grille */
    Vecteur grilleInclinaison;
    if (!jsonObject.HasMember("inclinaison_grille") || !jsonObject["inclinaison_grille"].IsArray() || jsonObject["inclinaison_grille"].GetArray().Size() != 3) {
        throw logic_error("Inclinaison de la grille manquante ou invalide");
    } else {
        const Value& coords = jsonObject["inclinaison_grille"];
        grilleInclinaison = Vecteur(coords[0].GetDouble(), coords[1].GetDouble(), coords[2].GetDouble());
    }

    return Grille(definitionLargeur, definitionHauteur, resolutionLargeur, resolutionHauteur, distanceFocale, grilleInclinaison);
}

vector<Lumiere> Parser::parseLumieres(Document& jsonObject) {
    vector<Lumiere> lumieres;

    if (jsonObject.HasMember("lumieres")) {
        if (!jsonObject["lumieres"].IsArray()) {
            throw logic_error("Les lumieres doivent être représentées sous forme d'un tableau d'objets JSON");
        }

        for (auto& lumiere : jsonObject["lumieres"].GetArray()) {
            lumieres.push_back(parseLumiere(lumiere));
        }
    }

    return lumieres;
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

Lumiere Parser::parseLumiere(Value& forme) {
    /* Récupération de la position de la lumière. */
    Point position;
    try {
        position = getPoint(forme, "position");
    } catch (logic_error le) {
        throw logic_error("Position de la lumière manquante ou invalide.");
    }

    /* Récupération de l'intensité lumineuse. */
    double intensite;
    if (!forme.HasMember("intensite")) {
        throw logic_error("intensitée de la lumière manquante.");
    } else {
        intensite = forme["intensite"].GetDouble();
    }

    return Lumiere(position, intensite);
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

    if (formeToUpperCase == "CYLINDRE") {
        return TypeForme::CYLINDRE;
    }

    if (formeToUpperCase == "PLAN") {
        return TypeForme::PLAN;
    }

    if (formeToUpperCase == "ELLIPSOIDE") {
        return TypeForme::ELLIPSOIDE;
    }

    if (formeToUpperCase == "CUBE") {
        return TypeForme::CUBE;
    }

    if (formeToUpperCase == "PAVE DROIT") {
        return TypeForme::PAVE_DROIT;
    }

    if (formeToUpperCase == "CONE") {
        return TypeForme::CONE;
    }

    return TypeForme::NONE;
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
            case TypeForme::CYLINDRE:
                return parseCylindre(forme);
                break;
            case TypeForme::PLAN:
                return parsePlan(forme);
                break;
            case TypeForme::ELLIPSOIDE:
                return parseEllipsoide(forme);
                break;
            case TypeForme::CUBE:
                return parseCube(forme);
                break;
            case TypeForme::PAVE_DROIT:
                return parsePaveDroit(forme);
                break;
            case TypeForme::CONE:
                return parseCone(forme);
                break;
            default:
                return nullptr;
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

Vecteur Parser::getRotation(Value& forme) {
    Vecteur rotation;

    if (!forme.HasMember("rotation")) {
        return rotation;
    } else {
        if (!forme["rotation"].IsArray() || forme["rotation"].GetArray().Size() != 3) {
            throw logic_error("La rotation de la forme doit être représentée sous la forme d'un tableau de 3 décimaux");
        }
        const Value& coords = forme["rotation"];
        rotation = Vecteur(coords[0].GetDouble(), coords[1].GetDouble(), coords[2].GetDouble());
    }

    return rotation;
}

Materiau Parser::getMateriau(Value& forme) {
    /* Récupération de la couleur */
    Couleur couleur = getCouleur(forme);

    /* Récupération de la spécularité */
    Couleur specularite = getSpecularite(forme);

    /* Récuperation de la valeur de brillance. */
    int brillance;
    if (!forme.HasMember("brillance")) {
        brillance = 0;
    } else {
        brillance = forme["brillance"].GetInt();
    }

    /* Récuperation de la valeur du coefficient de diffusion. */
    float coeffDiffusion;
    if (!forme.HasMember("coeff_diffusion")) {
        coeffDiffusion = 1;
    } else {
        coeffDiffusion = forme["coeff_diffusion"].GetFloat();
    }

    /* Récuperation de la valeur du coefficient de reflexion. */
    float reflexion;
    if (!forme.HasMember("reflexion")) {
        reflexion = 0;
    } else {
        reflexion = forme["reflexion"].GetFloat();
    }

    /* Récuperation de la valeur du coefficient de refraction. */
    float coeffRefraction;
    if (!forme.HasMember("coeff_refraction")) {
        coeffRefraction = 0;
    } else {
        coeffRefraction = forme["coeff_refraction"].GetFloat();
    }

    /* Récuperation de la valeur de l'indice de refraction. */
    float indiceRefraction;
    if (!forme.HasMember("indice_refraction")) {
        indiceRefraction = 1;
    } else {
        indiceRefraction = forme["indice_refraction"].GetFloat();
    }

    return Materiau(couleur, brillance, specularite, coeffDiffusion, reflexion, coeffRefraction, indiceRefraction);
}

Couleur Parser::getCouleur(Value& forme) {
    float r = 0, g = 0, b = 0;

    if (!forme.HasMember("couleur") || !forme["couleur"].IsString()) {
        return Couleur();
    } else {
        const Value& codeCouleur = forme["couleur"];

        try {
            r = stoi(string(codeCouleur.GetString()).substr(0, 2), nullptr, 16) / 255.0f;
            g = stoi(string(codeCouleur.GetString()).substr(2, 2), nullptr, 16) / 255.0f;
            b = stoi(string(codeCouleur.GetString()).substr(4, 2), nullptr, 16) / 255.0f;
        } catch (...) {
            throw logic_error("Le code couleur d'une forme est mal formé");
        }
    }

    return Couleur(r, g, b);
}

Couleur Parser::getSpecularite(Value& forme) {
    float r = 0, g = 0, b = 0;

    if (forme.HasMember("specularite")) {
        const Value& codeCouleur = forme["specularite"];

        try {
            r = stoi(string(codeCouleur.GetString()).substr(0, 2), nullptr, 16) / 255.0f;
            g = stoi(string(codeCouleur.GetString()).substr(2, 2), nullptr, 16) / 255.0f;
            b = stoi(string(codeCouleur.GetString()).substr(4, 2), nullptr, 16) / 255.0f;
        } catch (...) {
            throw logic_error("Le code couleur de la spécularité d'une forme est mal formé");
        }
    }

    return Couleur(r, g, b);
}

Sphere* Parser::parseSphere(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

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

    return new Sphere(centre, rayon, rotation, materiau);
}

Rectangle* Parser::parseRectangle(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Détermination du centre */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Centre du rectangle manquant ou invalide.");
    }

    /* D�termination de la normale du rectangle */
    Point normale;
    try {
        normale = getPoint(forme, "normale");
    } catch (logic_error le) {
        throw logic_error("Normale au rectangle manquante ou invalide.");
    }

    /* Détermination de la largeur */
    double largeur;
    if (!forme.HasMember("largeur")) {
        throw logic_error("Largeur du rectangle manquant.");
    } else {
        largeur = forme["largeur"].GetDouble();
    }

    /* Détermination de la longueur */
    double longueur;
    if (!forme.HasMember("longueur")) {
        throw logic_error("Longueur du rectangle manquant.");
    } else {
        longueur = forme["longueur"].GetDouble();
    }

    return new Rectangle(centre, Vecteur(normale.x, normale.y, normale.z), largeur, longueur, rotation, materiau);
}

Triangle* Parser::parseTriangle(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

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

    return new Triangle(pointA, pointB, pointC, rotation, materiau);
}

Cylindre* Parser::parseCylindre(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Détermination du centre du cylindre */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Centre du cylindre manquant ou invalide.");
    }

    /* Récupération de la hauteur du cylindre. */
    double hauteur;
    if (!forme.HasMember("hauteur")) {
        throw logic_error("Hauteur du cylindre manquant.");
    } else {
        hauteur = forme["hauteur"].GetDouble();
    }

    /* Récupération du rayon du cylindre. */
    double rayon;
    if (!forme.HasMember("rayon")) {
        throw logic_error("Rayon du cylindre manquant.");
    } else {
        rayon = forme["rayon"].GetDouble();
    }

    return new Cylindre(centre, hauteur, rayon, rotation, materiau);
}

Plan* Parser::parsePlan(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Détermination du point par lequel le plan passe */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Point du plan manquant ou invalide.");
    }

    /* Détermination de la normale au plan */
    Point normale;
    try {
        normale = getPoint(forme, "normale");
    } catch (logic_error le) {
        throw logic_error("Normale au plan manquante ou invalide.");
    }

    return new Plan(centre, Vecteur(normale.x, normale.y, normale.z), rotation, materiau);
}

Ellipsoide* Parser::parseEllipsoide(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Détermination du centre de l'ellipsoide */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Point de l'ellipsoide manquant ou invalide.");
    }

    /* Détermination du rayon A */
    double rayonA;
    if (!forme.HasMember("rayonA")) {
        throw logic_error("Rayon A de l'ellipsoide manquant.");
    } else {
        rayonA = forme["rayonA"].GetDouble();
    }

    /* Détermination du rayon B */
    double rayonB;
    if (!forme.HasMember("rayonB")) {
        throw logic_error("Rayon B de l'ellipsoide manquant.");
    } else {
        rayonB = forme["rayonB"].GetDouble();
    }

    /* Détermination du rayon C */
    double rayonC;
    if (!forme.HasMember("rayonC")) {
        throw logic_error("Rayon C de l'ellipsoide manquant.");
    } else {
        rayonC = forme["rayonC"].GetDouble();
    }

    return new Ellipsoide(centre, rayonA, rayonB, rayonC, rotation, materiau);
}

Cube* Parser::parseCube(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Récupération du centre du cube. */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Position du cube manquante ou invalide.");
    }

    /* Récupération de la taille du cube. */
    double taille;
    if (!forme.HasMember("taille")) {
        throw logic_error("Taille du cube manquante ou invalide.");
    } else {
        taille = forme["taille"].GetDouble();
    }

    return new Cube(centre, taille, rotation, materiau);
}

PaveDroit* Parser::parsePaveDroit(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Récupération du centre du cube. */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Position du pavé droit manquante ou invalide.");
    }

    /* Récupération de la largeur du pavé droit. */
    double largeur;
    if (!forme.HasMember("largeur")) {
        throw logic_error("Largeur du pavé droit manquante ou invalide.");
    } else {
        largeur = forme["largeur"].GetDouble();
    }

    /* Récupération de la hauteur du pavé droit. */
    double hauteur;
    if (!forme.HasMember("hauteur")) {
        throw logic_error("Hauteur du pavé droit manquante ou invalide.");
    } else {
        hauteur = forme["hauteur"].GetDouble();
    }

    /* Récupération de la profondeur du pavé droit. */
    double profondeur;
    if (!forme.HasMember("profondeur")) {
        throw logic_error("Profondeur du pavé droit manquante ou invalide.");
    } else {
        profondeur = forme["profondeur"].GetDouble();
    }

    return new PaveDroit(centre, largeur, hauteur, profondeur, rotation, materiau);
}

Cone* Parser::parseCone(Value& forme) {
    /* Récupération du materiau */
    Materiau materiau = getMateriau(forme);

    /* Récupération du vecteur de rotation */
    Vecteur rotation = getRotation(forme);

    /* Récupération du centre du cone. */
    Point centre;
    try {
        centre = getPoint(forme, "centre");
    } catch (logic_error le) {
        throw logic_error("Position du cone manquante ou invalide.");
    }

    /* Récupération du rayon du cone. */
    double rayon;
    if (!forme.HasMember("rayon")) {
        throw logic_error("Rayon du cone manquant ou invalide.");
    } else {
        rayon = forme["rayon"].GetDouble();
    }

    /* Récupération de la taille en hauteur du cone. */
    double hauteur;
    if (!forme.HasMember("hauteur")) {
        throw logic_error("Hauteur du cone manquante ou invalide.");
    } else {
        hauteur = forme["hauteur"].GetDouble();
    }

    return new Cone(centre, rayon, hauteur, rotation, materiau);
}

cxxopts::ParseResult Parser::parseArguments(int argc, char* argv[]) {
    cxxopts::Options options("lray", "Application implémentant le principe du lancer de rayon");

    options.add_options()
        ("n,niveau", "Niveau de rendu", cxxopts::value<int>())
        ("p,ps", "Nombre de rayons par pixel", cxxopts::value<int>())
        ("i,input", "Fichier de configuration json", cxxopts::value<string>())
        ("o,output", "Nom de l'image de sortie", cxxopts::value<string>())
        ("f,force", "Force le rendu en mode interactif")
        ("h,help", "Affiche ce message");

    auto resultat = options.parse(argc, argv);

    if (resultat.count("help")) {
        std::cout << options.help() << std::endl;
        exit(EXIT_SUCCESS);
    }

    return resultat;
}