#include "object/BoxTreeObject.h"

BoxTreeNode::BoxTreeNode(Triangle * tri) {
    box = BoundingBox(tri);
    triangles.push_back(tri);
    left = nullptr;
    right = nullptr;
    leafFlag = true;
}

BoxTreeNode::BoxTreeNode(vector<Triangle *> & tris) : BoxTreeNode(tris, 0, tris.size()) {}

BoxTreeNode::BoxTreeNode(vector<Triangle *> & tris, int start, int amount) {
    
    // Construct Bounding Box
    box = BoundingBox();
    for (int i = start; i < start + amount; i++) {
        box.extend(*tris[i]);
    }
    
    // Get the dimension data and midpoint from the bounding box
    vec3 dimension = box.getSize();
    int axis = maxAxis(dimension);
    float mid = box.getMinCorner()[axis] + dimension[axis] / 2.0f;
    
    // Check the amount
    if (amount == 0) {
        leafFlag = false;
    }
    else if (amount == 1) {
        leafFlag = true;
        triangles.push_back(tris[start]);
    }
    else if (amount == 2) {
        leafFlag = false;
        left = new BoxTreeNode(tris[start]);
        right = new BoxTreeNode(tris[start + 1]);
    }
    else {
        
        // Put all the left triangles to the left of this part of array
        int curr = start;
        for (int i = start; i < start + amount; i++) {
            if (tris[i]->getCenter()[axis] < mid) {
                swap(tris[i], tris[curr]);
                curr++;
            }
        }
        
        // Check if the left amount is 0 or all
        int la = curr - start;
        if (la == 0 || la == amount) {
            
            // Then store all the triangles in the array
            for (int i = start; i < start + amount; i++) {
                triangles.push_back(tris[i]);
            }
            leafFlag = true;
        }
        else {
            
            // Construct down to next level of nodes
            left = new BoxTreeNode(tris, start, la);
            right = new BoxTreeNode(tris, start + la, amount - la);
            box = BoundingBox::combine(left->getBoundingBox(), right->getBoundingBox());
            leafFlag = false;
        }
    }
}

BoxTreeNode::~BoxTreeNode() {
    if (!isLeaf()) {
        delete left;
        delete right;
    }
}

BoxTreeNode & BoxTreeNode::getLeft() {
    return *left;
}

BoxTreeNode & BoxTreeNode::getRight() {
    return *right;
}

BoundingBox & BoxTreeNode::getBoundingBox() {
    return box;
}

bool BoxTreeNode::leftRightIntersect() {
    if (isLeaf()) {
        return false;
    }
    return left->getBoundingBox().intersect(right->getBoundingBox());
}

bool BoxTreeNode::isLeaf() {
    return leafFlag;
}

bool BoxTreeNode::intersect(Ray & ray, Intersection & intersection) {
    bool hit = false;
    if (isLeaf()) {
        
        // Since this is the leaf, check through all the triangled
        for (int i = 0; i < triangles.size(); i++) {
            hit = hit || triangles[i]->intersect(ray, intersection, 0);
        }
        return hit;
    }
    else {
        
        // Prepare all the variables
        BoundingBox & b1 = left->getBoundingBox(), & b2 = right->getBoundingBox();
        float t1 = 0, t2 = 0;
        bool i1 = b1.intersect(ray, t1), i2 = b2.intersect(ray, t2);
        if (t1 < t2) {
            
            // First t1 then t2
            i1 = i1 && intersection.needUpdate(t1) && left->intersect(ray, intersection);
            i2 = i2 && intersection.needUpdate(t2) && right->intersect(ray, intersection);
        }
        else {
            
            // First t2 then t1
            i2 = i2 && intersection.needUpdate(t2) && right->intersect(ray, intersection);
            i1 = i1 && intersection.needUpdate(t1) && left->intersect(ray, intersection);
        }
        
        return i1 || i2;
    }
}

void BoxTreeObject::forceConstruct() {
    root = new BoxTreeNode(triangles);
}

void BoxTreeObject::constructTree() {
    if (!root) {
        forceConstruct();
    }
}

vector<vec3> BoxTreeObject::getBoundingVertices() {
    constructTree();
    return root->getBoundingBox().getBoundingVertices();
}

bool BoxTreeObject::updateIntersect(Ray & ray, Intersection & intersection, float t) {
    constructTree();
    BoundingBox box = root->getBoundingBox();
    if (box.intersect(ray)) {
        return root->intersect(ray, intersection);
    }
    return false;
}

BoxTreeObject::BoxTreeObject() : MeshObject() {
    root = nullptr;
}

BoxTreeObject::BoxTreeObject(const char * filename) : MeshObject(filename) {
    root = nullptr;
    constructTree();
}

BoxTreeObject::~BoxTreeObject() {
    delete root;
}

void BoxTreeObject::initiate() {
    constructTree();
}
