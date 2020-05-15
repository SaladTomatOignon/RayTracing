#include "../../include/scene/pixel.h"

Pixel::Pixel() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Pixel::Pixel(const Pixel& pixel) : Pixel(pixel.r, pixel.g, pixel.b) {

}

Pixel::~Pixel() {

}