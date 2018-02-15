#ifndef OBJECT_H
#define OBJECT_H

#include "utility/Transform.h"
#include "utility/Intersection.h"
#include "utility/Ray.h"
#include "material/Material.h"

namespace recartyar {
    class Object {
    public:
        
        Transform transform;
        Material * material;
        
        Object();
        
        bool hasMaterial();
        void setMaterial(Material & mtl);
        Material & getMaterial();
        
        virtual bool intersect(Ray & ray, Intersection & itsct);
    };
}

#endif
