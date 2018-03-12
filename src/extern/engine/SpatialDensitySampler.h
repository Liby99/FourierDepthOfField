#ifndef SPATIAL_DENSITY_SAMPLER_H
#define SPATIAL_DENSITY_SAMPLER_H

#include "engine/QuasiSampler.h"
#include "image/Image.h"

namespace recartyar {
    class SpatialDensitySampler : public quasisampler::QuasiSampler {
    private:
        Image * img;
    public:
        explicit SpatialDensitySampler(Image & spatialDensityImage);
        unsigned getImportanceAt(quasisampler::Point2D pt) override;
    };
}

#endif
