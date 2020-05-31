#include "../../include/application/context.h"

#include <string>

Context::Context() : Context("sortie.ppm", 1, 1, false, false, false, false) {

}

Context::Context(string fichierSortie, int niveau, int sampling, bool eclairageActive, bool ombrageActive, bool reflexionActive, bool transparenceActive) {
    this->fichierSortie = fichierSortie;
    this->niveau = niveau;
    this->sampling = sampling;
    this->eclairageActive = eclairageActive;
    this->ombrageActive = ombrageActive;
    this->reflexionActive = reflexionActive;
    this->transparenceActive = transparenceActive;
}

Context::~Context() {

}