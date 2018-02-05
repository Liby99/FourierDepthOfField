#ifndef RAY_H
#define RAY_H

#include "util/Transform.h"

class Ray {
protected:
    
    // Constants
    const static float INCREMENT;
    
    // Basic Ray Parameter
    vec3 origin;
    vec3 direction;
    int depth;
    bool inside;
    
public:
    
    // Constructors
    Ray();
    Ray(vec3 origin, vec3 direction);
    Ray(vec3 origin, vec3 direction, int depth);
    Ray(vec3 origin, vec3 direction, int depth, bool inside);
    
    // Setter
    vec3 getOrigin();
    void setOrigin(vec3 origin);
    vec3 getDirection();
    void setDirection(vec3 direction);
    int getDepth();
    void setDepth(int depth);
    bool isInside();
    void setInside(bool inside);
    
    vec3 getPoint(float t);
    
    void increment();
    void increment(vec3 direction);
    
    // Transform
    Ray transform(mat4 transf);
    Ray inverseTransform(mat4 transf);
};

#endif
