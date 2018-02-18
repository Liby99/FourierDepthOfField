#ifndef LAMBERT_H
#define LAMBERT_H

#include "material/Material.h"

namespace recartyar {
    class Lambert : public Material {
    public:
        Color color;
        Lambert();
        Lambert(Color color);
        virtual Color brdf(Intersection & itsct, Ray & out);
        virtual std::pair<Ray, Color> reflect(Intersection & itsct);
        virtual Color emission();
    };
}

#endif
