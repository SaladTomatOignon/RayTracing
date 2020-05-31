#ifndef DEF__CONTEXT
#define DEF__CONTEXT

#include <string>

using namespace std;

class Context {
    public:
        Context(string fichierSortie, int niveau, int sampling, bool eclairageActive, bool ombrageActive, bool reflexionActive, bool transparenceActive);
        Context();
        ~Context();

        string fichierSortie;
        int niveau;
        int sampling;
        bool eclairageActive;
        bool ombrageActive;
        bool reflexionActive;
        bool transparenceActive;
};

#endif