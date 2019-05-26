#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>
#include "utility/Ray.h"

namespace fdof {

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
        BoundingBox(const vec3 &minCorner, const vec3 &maxCorner);
        BoundingBox(Object * obj);

        inline float getWidth() const {
            return maxCorner.x - minCorner.x;
        }

        inline float getHeight() const {
            return maxCorner.y - minCorner.y;
        }

        inline float getLength() const {
            return maxCorner.z - minCorner.z;
        }

        inline vec3 getSize() const {
            return vec3(getWidth(), getHeight(), getLength());
        }

        // Basic getter
        inline const vec3 &getMinCorner() const {
            return minCorner;
        }

        inline const vec3 &getMaxCorner() const {
            return maxCorner;
        }

        inline vec3 getCenter() const {
            return (minCorner + maxCorner) / 2.0f;
        }

        // Basic setter
        inline void setMinCorner(const vec3 &minCorner) {
            this->minCorner = minCorner;
        }

        inline void setMaxCorner(const vec3 &maxCorner) {
            this->maxCorner = maxCorner;
        }

        // Extend the box to a new bound
        void extend(const vec3 &v);
        void extend(Object &object);
        void extend(const BoundingBox &box);

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
