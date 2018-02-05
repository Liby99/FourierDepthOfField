#ifndef IMAGE_H
#define IMAGE_H

#include "utility/Color.h"

namespace fdof {
    class Image {
    public:
        int width;
        int height;
        Color * pixels;
        Image(int width, int height);
        ~Image();
        Color & getColor(int x, int y);
        void setColor(int x, int y, Color & color);
    };
}

#endif
