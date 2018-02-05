#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

#include "util/Color.h"

class Image {
protected:
    
    // Basic parameters
    int width;
    int height;
    Color * pixels;
    
    void clearPixels();
    
public:
    
    // Constructor and destructor
    Image(int width, int height);
    ~Image();
    
    void resize(int width, int height);
    
    //
    int getWidth();
    int getHeight();
    
    //
    Color & getPixel(int x, int y);
    void setPixel(int x, int y, Color color);
};

#endif
