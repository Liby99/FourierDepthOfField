#ifndef SPECTRUM_H
#define SPECTRUM_H

#include "utility/Math.h"

namespace recartyar {
    class Spectrum {
    public:
        std::vector<vec2> samples;
        Spectrum(int num);
        void transport(float dist);
    };
}

#endif
