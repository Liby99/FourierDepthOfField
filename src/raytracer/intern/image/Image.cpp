#include "image/Image.h"

void Image::clearPixels() {
    delete [] pixels;
}

Image::Image(int width, int height) : pixels(nullptr) {
    resize(width, height);
}

Image::~Image() {
    clearPixels();
}

void Image::resize(int width, int height) {
    if (this->pixels) {
        Color * newPixels = new Color[width * height];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (i < this->width && j < this->height) {
                    newPixels[i + j * width] = getPixel(i, j);
                }
                else {
                    newPixels[i + j * width] = Color();
                }
            }
        }
        clearPixels();
        pixels = newPixels;
    }
    else {
        this->width = width;
        this->height = height;
        this->pixels = new Color[width * height];
    }
}

int Image::getWidth() {
    return width;
}

int Image::getHeight() {
    return height;
}

Color & Image::getPixel(int x, int y) {
    return pixels[x + y * width];
}

void Image::setPixel(int x, int y, Color color) {
    pixels[x + y * width] = color;
}
