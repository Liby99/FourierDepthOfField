#ifndef BOX_TREE_OBJECT_H
#define BOX_TREE_OBJECT_H

#include "object/MeshObject.h"
#include "object/Triangle.h"

class BoxTreeNode {
protected:
    
    // Left and right nodes if not leaf
    BoxTreeNode * left;
    BoxTreeNode * right;
    
    // Variables
    vector<Triangle *> triangles;
    BoundingBox box;
    bool leafFlag;
    
    // Protected constructor, only used for internal call
    BoxTreeNode(vector<Triangle *> & tris, int start, int amount);
    
public:
    
    // Constructor
    BoxTreeNode(Triangle * tris);
    BoxTreeNode(vector<Triangle *> & tris);
    ~BoxTreeNode();
    
    // Getter
    BoxTreeNode & getLeft();
    BoxTreeNode & getRight();
    BoundingBox & getBoundingBox();
    
    // Helper Methods
    bool leftRightIntersect();
    bool isLeaf();
    bool intersect(Ray & ray, Intersection & intersection);
};

class BoxTreeObject : public MeshObject {
protected:
    
    BoxTreeNode * root;
    
    // Helper construct method
    void forceConstruct();
    void constructTree();
    
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    
public:
    
    //
    BoxTreeObject();
    BoxTreeObject(const char * filename);
    ~BoxTreeObject();
    
    void initiate();
};

#endif
