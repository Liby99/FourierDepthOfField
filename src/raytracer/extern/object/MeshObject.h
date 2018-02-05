#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include "object/Object.h"
#include "object/Triangle.h"
#include "util/Vertex.h"

#include <string.h>

class MeshObject : public Object {
protected:
    
    // Vertex and Triangle Array
    vector<Vertex *> vertices;
    vector<Triangle *> triangles;
    
    // Helper Corner Method
    void getCorner(vec3 minCorner, vec3 maxCorner);
    
    // Intersect
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    virtual vec3 sampleSurfacePointHelper(float t);
    
public:
    
    // Constructor and Destructor
    MeshObject();
    MeshObject(const char * filename);
    ~MeshObject();
    
    // Vertex and Triangle Manipulation
    int addVertex(vec3 position);
    int addVertex(vec3 position, vec3 normal);
    int addTriangle(int i0, int i1, int i2);
    
    // Destructor helper methods
    void clear();
    void clearVertices();
    void clearTriangles();
    
    // Load object from file
    bool loadPly(const char * filename);
    void smooth();
};

#endif
