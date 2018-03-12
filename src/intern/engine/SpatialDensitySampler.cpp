#include "engine/SpatialDensitySampler.h"

using namespace recartyar;

SpatialDensitySampler::SpatialDensitySampler(Image & spatialDensityImage) :
        QuasiSampler(spatialDensityImage.width, spatialDensityImage.height) {
    this->img = &spatialDensityImage;
}

unsigned SpatialDensitySampler::getImportanceAt(quasisampler::Point2D pt) {
    return (unsigned) img->getRawColor((int) pt.x, (int) pt.y).r;
}