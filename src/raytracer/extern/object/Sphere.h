#ifndef SPHERE_H
#define SPHERE_H

#include "object/Object.h"

class Sphere : public Object {
private:
    
    // Basic
    float radius;
    
protected:
    
    // Inherited intersect
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    virtual vec3 sampleSurfacePointHelper(float t);
    
public:
    
    // Constructer
    Sphere();
    Sphere(float radius);
    
    // Basic getter and setter
    float getRadius();
    void setRadius(float radius);
};

#endif
