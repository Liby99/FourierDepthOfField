#ifndef SPATIAL_DENSITY_SAMPLER_H
#define SPATIAL_DENSITY_SAMPLER_H

#include <quasisampler_prototype.h>
#include "image/Image.h"

namespace recartyar {
    class SpatialDensitySampler : public quasi_sampler::Quasisampler {
    private:
        Image * img;
    public:
        explicit SpatialDensitySampler(Image & spatialDensityImage);
        unsigned getImportanceAt(quasi_sampler::Point2D pt) override;
    };
}

#endif
