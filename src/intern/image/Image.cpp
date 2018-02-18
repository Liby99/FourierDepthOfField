#include "image/Image.h"

using namespace recartyar;

Image::Image(int width, int height) {
    initiate(width, height);
}

Image::~Image() {
    clear();
}

void Image::resize(int width, int height) {
    clear();
    initiate(width, height);
}

Color Image::getColor(int x, int y) {
    if (addCounts[y * width + x] == 0) {
        return pixels[y * width + x];
    }
    else {
        return pixels[y * width + x] / addCounts[y * width + x];
    }
}

void Image::setColor(int x, int y, Color color) {
    pixels[y * width + x] = color;
    addCounts[y * width + x] = 0;
}

void Image::addColor(int x, int y, Color color) {
    pixels[y * width + x] += color;
    addCounts[y * width + x]++;
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

void Image::clear() {
    delete [] pixels;
    delete [] addCounts;
}

void Image::initiate(int width, int height) {
    this->width = width;
    this->height = height;
    this->pixels = new Color[width * height];
    this->addCounts = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        addCounts[i] = 0;
    }
}
