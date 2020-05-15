#ifndef DEF__PIXEL
#define DEF__PIXEL

class Pixel {
    public:
        Pixel();
        Pixel(unsigned char r, unsigned char g, unsigned char b);
        Pixel(const Pixel& pixel);
        ~Pixel();

        unsigned char r, g, b;
};

#endif