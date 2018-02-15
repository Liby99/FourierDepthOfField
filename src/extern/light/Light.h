#ifndef LIGHT_H
#define LIGHT_H

#include "utility/Color.h"
#include "utility/Ray.h"
#include "utility/Intersection.h"

namespace recartyar {
    class Light {
    public:
        Color color;
        float intensity;
        Light();
        Light(Color color);
        bool intersect(Ray & ray, Intersection & itsct);
        virtual float getBrightness(Intersection & objItsct, Intersection & lgtItsct);
        virtual glm::vec3 getToLightDir(Intersection & itsct);
    };
}

#endif
