#ifndef CUBE_H
#define CUBE_H

#include "object/Object.h"

namespace recartyar {
    class Cube : public Object {
    public:
        float width;
        float height;
        float length;
        Cube();
        Cube(float width, float height, float length);
        virtual bool intersect(Ray & ray, Intersection & itsct);
    };
}

#endif
