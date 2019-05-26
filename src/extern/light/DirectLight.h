#ifndef DIRECT_LIGHT_H
#define DIRECT_LIGHT_H

#include "light/Light.h"

namespace fdof {
    class DirectLight : public Light {
    public:
        vec3 direction;
        DirectLight();
        DirectLight(vec3 dir);
        DirectLight(Color color, vec3 dir);
        virtual float getBrightness(Intersection & objItsct, Intersection & lgtItsct);
        virtual vec3 getToLightDir(Intersection & itsct);
    };
}

#endif
