#include "utility/SpectrumRay.h"

using namespace fdof;

SpectrumRay::SpectrumRay() : SpectrumRay(vec3(), vec3(0, 0, 1)) {}

SpectrumRay::SpectrumRay(const Ray & r) : SpectrumRay(r.origin, r.direction) {}

SpectrumRay::SpectrumRay(vec3 origin, vec3 direction) : Ray(origin, direction) {
    spectrum = new Spectrum(10);
}

SpectrumRay::~SpectrumRay() {
    delete spectrum;
}