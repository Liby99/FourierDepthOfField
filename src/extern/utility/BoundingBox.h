#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>
#include "utility/Ray.h"

namespace recartyar {
    
    class Object;
    
    class BoundingBox {
    private:
        
        // Basic parameters
        bool initiated;
        vec3 minCorner;
        vec3 maxCorner;
        
    public:
        
        // Constructor
        BoundingBox();
        BoundingBox(vec3 minCorner, vec3 maxCorner);
        BoundingBox(Object * obj);
        
        float getWidth();
        float getHeight();
        float getLength();
        vec3 getSize();
        
        // Basic getter
        vec3 getMinCorner();
        vec3 getMaxCorner();
        vec3 getCenter();
        
        // Basic setter
        void setMinCorner(vec3 minCorner);
        void setMaxCorner(vec3 maxCorner);
        
        // Extend the box to a new bound
        void extend(vec3 v);
        void extend(Object & object);
        void extend(BoundingBox box);
        
        // Contains vector
        bool contains(vec3 vec);
        
        // Check intersect
        bool intersect(Ray & ray);
        bool intersect(Ray & ray, float t);
        bool intersect(Object & object);
        bool intersect(BoundingBox box);
        
        void combine(BoundingBox & box);
        
        static BoundingBox combine(BoundingBox & b1, BoundingBox & b2);
        static vec3 minVec(vec3 a, vec3 b);
        static vec3 maxVec(vec3 a, vec3 b);
    };
}

#endif
