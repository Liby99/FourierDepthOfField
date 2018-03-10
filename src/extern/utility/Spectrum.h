#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <vector>
#include "utility/Sampler.h"
#include "utility/Math.h"

namespace recartyar {
    class Spectrum {
    public:

        std::vector<vec2> samples;

        explicit Spectrum(int num);
        void transport(float dist);
        void occlude(Spectrum & other);
    };
}

#endif