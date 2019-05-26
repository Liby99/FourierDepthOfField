#ifndef BOX_TREE_H
#define BOX_TREE_H

#include "object/Object.h"
#include "utility/BoundingBox.h"

namespace fdof {

    class BoxTreeNode {
    protected:

        BoxTreeNode * left;
        BoxTreeNode * right;
        std::vector<Object *> objects;
        BoundingBox box;
        bool leafFlag;

    public:

        explicit BoxTreeNode(Object * obj);
        explicit BoxTreeNode(std::vector<Object *> & objs);
        ~BoxTreeNode();

        inline BoxTreeNode & getLeft();
        inline BoxTreeNode & getRight();
        inline BoundingBox & getBoundingBox();

        bool leftRightIntersect();
        bool isLeaf();
        bool intersect(Ray & ray, Intersection & itsct);

    protected:

        BoxTreeNode(std::vector<Object *> & objs, int start, int amount);
        static int maxAxis(vec3 dimension);
    };

    class BoxTree {
    public:
        BoxTreeNode * root;
        explicit BoxTree(std::vector<Object *> & objects);
        bool intersect(Ray & ray, Intersection & itsct);
    };
}

#endif
