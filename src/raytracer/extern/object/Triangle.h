#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object/Object.h"
#include "util/Vertex.h"
#include "util/Ray.h"

#include <stdexcept>

class Triangle : public Object {
private:
    
    // Vertices of triangle
    Vertex * v0;
    Vertex * v1;
    Vertex * v2;
    
    // Helper methods
    vec3 getBaryCentric(vec3 position);
    
protected:
    
    // Intersection with ray
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    virtual vec3 sampleSurfacePointHelper(float t);
    
public:
    
    // Constructor
    Triangle(Vertex * v0, Vertex * v1, Vertex * v2);
    
    // Getters
    Vertex & getVertex(int i);
    Vertex & getV0();
    Vertex & getV1();
    Vertex & getV2();
    
    // Get the gravity center of the triangle
    vec3 getCenter();
};

#endif
