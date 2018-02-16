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

void Image::setColor(int x, int y, Color color) {
    pixels[y * width + x] = color;
}

bool Image::save(const char * filename) {
    
    // Initiate
    int numPixels = width * height;
    int intPixels[numPixels];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            intPixels[i + width * j] = getColor(i, j).toInt();
        }
    }
    
    // Setup Header
    BitmapHeader head;
    head.fileSize = sizeof(BitmapHeader) + 2 + numPixels * sizeof(int);
    head.reserved = 0;
    head.startAddress = sizeof(BitmapHeader) + 2;
    head.headerSize = 12;
    head.width = width;
    head.height = height;
    head.colorPlanes = 1;
    head.bitsPerPixel = 32;
    
    // Start to write files
    FILE * f = fopen(filename, "wb");
    if (f == 0) {
        printf("Can't open '%s'\n", filename);
        return false;
    }
    short magic = 19778;
    fwrite(&magic, sizeof(short), 1, f);
    fwrite(&head, sizeof(BitmapHeader), 1, f);
    fwrite(intPixels, sizeof(int), numPixels, f);
    fclose(f);
    return true;
}
