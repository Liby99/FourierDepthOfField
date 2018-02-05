#ifndef LIGHT_H
#define LIGHT_H

#include "utility/Color.h"
#include "utility/Ray.h"
#include "utility/Intersection.h"

namespace fdof {
    class Light {
    public:
        Color color;
        float intensity;
        Light();
        Light(Color color);
        bool intersect(Ray & ray, Intersection & itsct);
    };
}

#endif
