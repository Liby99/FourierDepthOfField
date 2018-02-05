#ifndef MESH_CUBE_H
#define MESH_CUBE_H

#include "object/MeshObject.h"
#include "object/Cube.h"

class MeshCube : public Cube {
private:
    
    // Mesh instance. Adapter Structure
    MeshObject mesh;
    
    // Helper functions of constructing the cube
    void clear();
    void construct();
    void reconstruct();
    
protected:
    
    // Inherited intersect method
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    
public:
    
    // Constructor
    MeshCube();
    MeshCube(float width, float height, float length);
    
    // Basic getter and setter
    virtual void setWidth(float width);
    virtual void setHeight(float height);
    virtual void setLength(float length);
};

#endif
