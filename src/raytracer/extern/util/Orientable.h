#ifndef ORIENTABLE_H
#define ORIENTABLE_H

#include "util/Transform.h"

class Orientable {
protected:

    // Protected parameters
    int orientation;
    
public:
    
    // Public statics
    const static vec3 NORMALS[];
    const static int DEFAULT_ORIENTATION;
    const static int X_POSITIVE;
    const static int X_NEGATIVE;
    const static int Y_POSITIVE;
    const static int Y_NEGATIVE;
    const static int Z_POSITIVE;
    const static int Z_NEGATIVE;
    
    // Constructors
    Orientable();
    Orientable(int orientation);
    
    // Basic getter and setter
    int getOrientation();
    void setOrientation(int orientation);
    
    // Get the axis. 0 for x, 1 for y, 2 for z
    int getAxis();
};

#endif
