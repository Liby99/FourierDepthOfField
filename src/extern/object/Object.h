#ifndef OBJECT_H
#define OBJECT_H

#include "utility/Transform.h"
#include "utility/Intersection.h"
#include "utility/Ray.h"
#include "utility/BoundingBox.h"
#include "material/Material.h"

namespace fdof {
    class Object {
    public:

        Transform transform;
        Material * material;
        BoundingBox * box;

        Object();
        ~Object();

        bool hasMaterial();
        void setMaterial(Material & mtl);
        Material & getMaterial();
        BoundingBox & getBoundingBox();
        void initiateBoundingBox();
        virtual bool intersect(Ray & ray, Intersection & itsct);

    protected:

        virtual void getBoundingVertices(std::vector<vec3> & bvs);
        virtual bool updateIntersect(Ray & ray, Intersection & itsct);

        inline static vec3 transformHomogenous(const mat4 & m, const vec3 & v);
    };
}

#endif
