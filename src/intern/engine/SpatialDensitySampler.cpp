#include "engine/SpatialDensitySampler.h"

using namespace recartyar;

SpatialDensitySampler::SpatialDensitySampler(Image & sdimg) {
    this->img = &sdimg;
}

unsigned SpatialDensitySampler::getImportanceAt(quasisampler::Point2D pt) {
    return (unsigned) this->img->getRawColor(pt.x, pt.y).r;
}