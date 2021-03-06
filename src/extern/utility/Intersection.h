#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "utility/Ray.h"

namespace fdof {

    class Object;

    class Intersection {
    public:
        Ray * ray;
        Object * object;
        vec3 position;
        vec3 normal;
        float t;
        bool hit;
        Intersection(Ray & ray);
        bool hasObject();
        Object & getObject();
        void setObject(Object & object);
        Ray & getRay();
        void setRay(Ray & ray);
        float distToOrigin();
        bool needUpdate(float t);
        bool update(float t, vec3 position, vec3 normal);
        void transform(mat4 transf);
    };
}

#endif
