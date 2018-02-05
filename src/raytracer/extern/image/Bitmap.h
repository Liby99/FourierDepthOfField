#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>

#include "image/Image.h"

using namespace std;

class Bitmap : public Image {
public:
    
    // Constructor
    Bitmap(int x,int y);
    
    // Save image api
    bool saveImage(const char * filename);
    
    // Static save image method from a given image
    static bool saveImage(Image & image, const char * filename);
};

#endif
