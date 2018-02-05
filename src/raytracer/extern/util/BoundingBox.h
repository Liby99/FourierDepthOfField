#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "util/Ray.h"

#include <vector>

using namespace std;

class Object;

class BoundingBox {
private:
    
    // Basic parameters
    bool initiated;
    vec3 minCorner;
    vec3 maxCorner;
    
public:
    
    // Constructor
    BoundingBox();
    BoundingBox(vec3 minCorner, vec3 maxCorner);
    BoundingBox(Object * obj);
    
    float getWidth();
    float getHeight();
    float getLength();
    vec3 getSize();
    
    // Basic getter
    vec3 getMinCorner();
    vec3 getMaxCorner();
    vector<vec3> getBoundingVertices();
    
    // Basic setter
    void setMinCorner(vec3 minCorner);
    void setMaxCorner(vec3 maxCorner);
    
    // Extend the box to a new bound
    void extend(vec3 v);
    void extend(Object & object);
    void extend(BoundingBox box);
    
    // Contains vector
    bool contains(vec3 vec);
    
    // Check intersect
    bool intersect(Ray & ray);
    bool intersect(Ray & ray, float & t);
    bool intersect(Object & object);
    bool intersect(BoundingBox box);
    
    void combine(BoundingBox & box);
    
    static BoundingBox combine(BoundingBox & b1, BoundingBox & b2);
};

#endif
