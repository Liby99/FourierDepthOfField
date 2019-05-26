#ifndef SPECTRUM_H
#define SPECTRUM_H

#include <vector>
#include "image/Image.h"
#include "utility/Sampler.h"
#include "utility/Math.h"

namespace fdof {
    class Spectrum {
    public:

        std::vector<vec2> samples;

        explicit Spectrum(int num);
        void transport(float dist);
        void occlude(float ox);
        void filterAperture(float aperture, float focalDistance);

        float getVariance(float focalDistance);
        float getMaximumBandwidth();

        void saveImage(const std::string & name);
    };
}

#endif