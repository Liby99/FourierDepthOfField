#ifndef BOX_TREE_OBJECT_H
#define BOX_TREE_OBJECT_H

#include "object/MeshObject.h"

namespace fdof {

    class BoxTreeObjectNode {
    protected:

        // Left and right nodes if not leaf
        BoxTreeObjectNode * left;
        BoxTreeObjectNode * right;

        // Variables
        std::vector<Triangle *> triangles;
        BoundingBox box;
        bool leafFlag;

        // Protected constructor, only used for internal call
        BoxTreeObjectNode(std::vector<Triangle *> & tris, int start, int amount);

    public:

        // Constructor
        BoxTreeObjectNode(Triangle * tris);
        BoxTreeObjectNode(std::vector<Triangle *> & tris);
        ~BoxTreeObjectNode();

        // Getter
        BoxTreeObjectNode & getLeft();
        BoxTreeObjectNode & getRight();
        BoundingBox & getBoundingBox();

        // Helper Methods
        bool leftRightIntersect();
        bool isLeaf();
        bool intersect(Ray & ray, Intersection & intersection);

        int maxAxis(vec3 dimension) {
            float max = dimension[0], maxIndex = 0;
            for (int i = 1; i < 3; i++) {
                if (dimension[i] > max) maxIndex = i;
            }
            return maxIndex;
        }
    };

    class BoxTreeObject : public MeshObject {
    protected:

        BoxTreeObjectNode * root;

        // Helper construct method
        void forceConstruct();
        void constructTree();

        virtual void getBoundingVertices(std::vector<vec3> & verts);
        virtual bool updateIntersect(Ray & ray, Intersection & intersection) const;

    public:

        //
        BoxTreeObject();
        BoxTreeObject(const char * filename);
        ~BoxTreeObject();

        void initiate();
    };
}
#endif
