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
        Color getColor(Intersection & objItsct, Intersection & lgtItsct);
        virtual float getBrightness(Intersection & objItsct, Intersection & lgtItsct);
        virtual vec3 getToLightDir(Intersection & itsct);
    };
}

#endif
