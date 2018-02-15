#include "image/Image.h"

using namespace recartyar;

Image::Image(int width, int height) : width(width), height(height) {
    pixels = new Color[width * height];
}

Image::~Image() {
    delete [] pixels;
}

void Image::resize(int width, int height) {
    delete [] pixels;
    this->width = width;
    this->height = height;
    this->pixels = new Color[width * height];
}

Color & Image::getColor(int x, int y) {
    return pixels[y * width + x];
}

void Image::setColor(int x, int y, Color & color) {
    pixels[y * width + x] = color;
}
