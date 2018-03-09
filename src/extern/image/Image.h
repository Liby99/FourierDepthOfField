#ifndef IMAGE_H
#define IMAGE_H

#include "utility/Color.h"

namespace recartyar {
    
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
    
    class Image {
    public:
        int width;
        int height;
        Color * pixels;
        int * addCounts;
        Image(int width, int height);
        ~Image();
        void resize(int width, int height);
        Color getRawColor(int x, int y);
        Color getColor(int x, int y);
        void setColor(int x, int y, Color color);
        void addColor(int x, int y, Color color);
        bool save(const char * filename);
    private:
        void clear();
        void initiate(int width, int height);
    };
}

#endif
