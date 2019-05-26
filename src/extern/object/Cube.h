#ifndef CUBE_H
#define CUBE_H

#include "object/Object.h"

namespace fdof {
    class Cube : public Object {
    public:
        float width;
        float height;
        float length;
        Cube();
        Cube(float width, float height, float length);
    protected:
        virtual void getBoundingVertices(std::vector<vec3> & bvs) override;
        virtual bool updateIntersect(Ray & ray, Intersection & itsct) override;
    };
}

#endif
