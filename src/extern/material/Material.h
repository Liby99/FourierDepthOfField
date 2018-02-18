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
        virtual Color getReflection(Intersection & i, Ray & out);
        virtual std::pair<Ray, Color> reflect(Intersection & intersection);
        virtual Color emission();
    };
}

#endif
