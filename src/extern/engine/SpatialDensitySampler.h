#ifndef SPATIAL_DENSITY_SAMPLER_H
#define SPATIAL_DENSITY_SAMPLER_H

#include "image/Image.h"
#include "engine/QuasiSampler.h"

namespace recartyar {
    class SpatialDensitySampler : public quasisampler::QuasiSampler {
    public:
        Image * img;
        SpatialDensitySampler(Image & sdimg);
        unsigned getImportanceAt(quasisampler::Point2D pt);
    };
}

#endif
