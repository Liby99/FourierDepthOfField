#ifndef MATERIAL_H
#define MATERIAL_H

#include <utility>

#include "utility/Color.h"
#include "utility/Intersection.h"
#include "utility/Ray.h"

namespace recartyar {
    class Material {
    public:
        Material();
        virtual std::pair<Ray, Color> generateSample(Intersection & intersection, vec2 sample);
        virtual Color computeReflection(Intersection & i, Ray & out);
        virtual Color emission();
    };
}

#endif
