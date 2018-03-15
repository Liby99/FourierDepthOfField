#ifndef DEPTH_TRACER_H
#define DEPTH_TRACER_H

#include <limits>
#include "engine/RenderEngine.h"

namespace recartyar {
    class DepthTracer : public RenderEngine {
    public:
        float mNear, mFar;
    protected:
        int currI, currJ;
        float hw, hh;
    public:
        DepthTracer();
        float near();
        void setNear(float n);
        float far();
        void setFar(float f);
        void initiateGenerator(Scene & scn, Image & img) override;
        RaySample getNextSample(Scene & scn, Image & img) override;
        bool hasNextSample(Scene & scn, Image & img) override;
        Color getColor(Scene & scn, Ray & ray) override;
    };
}

#endif
