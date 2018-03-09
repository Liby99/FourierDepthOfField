#include "scene/BoxTree.h"

using namespace recartyar;

BoxTreeNode::BoxTreeNode(Object * obj) {
    box = BoundingBox(obj);
    objects.push_back(obj);
    left = nullptr;
    right = nullptr;
    leafFlag = true;
}

BoxTreeNode::BoxTreeNode(std::vector<Object *> & objs) : BoxTreeNode(objs, 0, objs.size()) {}

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

bool BoxTreeNode::intersect(Ray & ray, Intersection & itsct) {
    bool hit = false;
    if (isLeaf()) {

        // Since this is the leaf, check through all the triangled
        for (int i = 0; i < objects.size(); i++) {
            hit = objects[i]->intersect(ray, itsct) || hit;
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
            i1 = i1 && itsct.needUpdate(t1) && left->intersect(ray, itsct);
            i2 = i2 && itsct.needUpdate(t2) && right->intersect(ray, itsct);
        }
        else {

            // First t2 then t1
            i2 = i2 && itsct.needUpdate(t2) && right->intersect(ray, itsct);
            i1 = i1 && itsct.needUpdate(t1) && left->intersect(ray, itsct);
        }

        return i1 || i2;
    }
}

BoxTreeNode::BoxTreeNode(std::vector<Object *> & objs, int start, int amount) {

    // Construct Bounding Box
    box = BoundingBox();
    for (int i = start; i < start + amount; i++) {
        box.extend(*objs[i]);
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
        objects.push_back(objs[start]);
    }
    else if (amount == 2) {
        leafFlag = false;
        left = new BoxTreeNode(objs[start]);
        right = new BoxTreeNode(objs[start + 1]);
    }
    else {

        // Put all the left triangles to the left of this part of array
        int curr = start;
        for (int i = start; i < start + amount; i++) {
            if (objs[i]->getBoundingBox().getCenter()[axis] < mid) {
                std::swap(objs[i], objs[curr]);
                curr++;
            }
        }

        // Check if the left amount is 0 or all
        int la = curr - start;
        if (la == 0 || la == amount) {

            // Then store all the triangles in the array
            for (int i = start; i < start + amount; i++) {
                objects.push_back(objs[i]);
            }
            leafFlag = true;
        }
        else {

            // Construct down to next level of nodes
            left = new BoxTreeNode(objs, start, la);
            right = new BoxTreeNode(objs, start + la, amount - la);
            box = BoundingBox::combine(left->getBoundingBox(), right->getBoundingBox());
            leafFlag = false;
        }
    }
}

int BoxTreeNode::maxAxis(vec3 dimension) {
    float max = dimension[0], maxIndex = 0;
    for (int i = 1; i < 3; i++) {
        if (dimension[i] > max) maxIndex = i;
    }
    return maxIndex;
}

BoxTree::BoxTree(std::vector<Object *> & objects) {
    root = new BoxTreeNode(objects);
}

bool BoxTree::intersect(Ray & ray, Intersection & itsct) {
    BoundingBox box = root->getBoundingBox();
    if (box.intersect(ray)) {
        return root->intersect(ray, itsct);
    }
    return false;
}
