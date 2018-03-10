#ifndef SPECTRUM_RAY_H
#define SPECTRUM_RAY_H

#include "utility/Ray.h"
#include "utility/Spectrum.h"

namespace recartyar {
    class SpectrumRay : public Ray {
    public:
        Spectrum * spectrum;
        SpectrumRay();
        SpectrumRay(const Ray & r);
        SpectrumRay(vec3 origin, vec3 direction);
        ~SpectrumRay();
    };
}

#endif