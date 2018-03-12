#include "engine/SpatialDensitySampler.h"

using namespace recartyar;

SpatialDensitySampler::SpatialDensitySampler(Image & spatialDensityImage) {
    this->img = &spatialDensityImage;
}

unsigned SpatialDensitySampler::getImportanceAt(quasi_sampler::Point2D pt) {
    return (unsigned) img->getRawColor(pt.x, pt.y).r;
}