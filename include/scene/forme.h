#ifndef DEF__FORME
#define DEF__FORME

class Forme {
    public:
        Forme();
        ~Forme();

        virtual Forme* clone() const = 0;
};

#endif