#ifndef IMAGE_H
#define IMAGE_H

#include "utility/Math.h"
#include "utility/Color.h"

#include <vector>

namespace fdof {

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

        // Basic
        void resize(int width, int height);
        Color getRawColor(int x, int y);
        Color getColor(int x, int y);
        void setColor(int x, int y, Color color);
        void addColor(int x, int y, Color color);

        // Convolutions
        void blur(int n);
        void convolve(int * filter, int n, int normalization, int absval);

        // File I/O
        bool save(const char * filename);

    private:
        void clear();
        void initiate(int width, int height);
    };
}

#endif
