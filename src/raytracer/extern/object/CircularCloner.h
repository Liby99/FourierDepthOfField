#ifndef CIRCULAR_CLONER_H
#define CIRCULAR_CLONER_H

#include "object/Cloner.h"

class CircularCloner : public Cloner {
protected:
    
    Animatable<float> radius;
    int count;
    
    void retransform(float t);
    void reconstruct();
    
public:
    
    CircularCloner(Object & object);
    CircularCloner(Object & object, float radius, int count);
    
    float getRadius(float t);
    void setRadius(float radius);
    void setRadius(float radius, int t);
    
    int getCount();
    void setCount(int count);
    
    virtual bool intersect(Ray & ray, Intersection & intersection, float t);
};

#endif
