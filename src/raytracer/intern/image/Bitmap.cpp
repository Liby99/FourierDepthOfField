#include "image/Bitmap.h"

struct BitmapHeader {
    int fileSize;
    int reserved;
    int startAddress;
    int headerSize;
    short width;
    short height;
    short colorPlanes;
    short bitsPerPixel;
};

Bitmap::Bitmap(int width, int height) : Image(width, height) {};

bool Bitmap::saveImage(const char * filename) {
    return Bitmap::saveImage(*this, filename);
}

bool Bitmap::saveImage(Image & image, const char * filename) {
    
    // Setup content
    int width = image.getWidth();
    int height = image.getHeight();
    int numPixels = width * height;
    int intPixels[numPixels];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            intPixels[i + width * j] = image.getPixel(i, j).toInt();
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
