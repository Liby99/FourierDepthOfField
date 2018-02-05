#include "image/Image.h"

using namespace fdof;

Image::Image(int width, int height) : width(width), height(height) {
    pixels = new Color[width * height];
}

Image::~Image() {
    delete [] pixels;
}

Color & Image::getColor(int x, int y) {
    return pixels[y * width + x];
}

void Image::setColor(int x, int y, Color & color) {
    pixels[y * width + x] = color;
}
