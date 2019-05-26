#ifndef RAY_H
#define RAY_H

#include "utility/Math.h"

namespace fdof {
    class Ray {
    public:
        int depth;
        vec3 origin;
        vec3 direction;
        Ray();
        Ray(vec3 origin, vec3 direction);
        vec3 getPoint(float t);
        void increment();
        Ray inverseTransform(mat4 transf);
        Ray transform(mat4 transf);
    };
};

#endif
