#ifndef DISCONTINUITY_TRACER_H
#define DISCONTINUITY_TRACER_H

#include "engine/DepthTracer.h"

namespace recartyar {
    class DiscontinuityTracer : public RenderEngine {
    public:
        DepthTracer depthTracer;
        virtual void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) override;
        bool hasDiscont(Scene & scn, Image & depthImg, int i, int j, int x, int y);
    };
}

#endif
