#ifndef DEPTH_TRACER_H
#define DEPTH_TRACER_H

#include <limits>
#include "engine/PathTracer.h"

namespace recartyar {
    class DepthTracer : public PathTracer {
    public:
        float mNear;
        float mFar;
        DepthTracer();
        float near();
        void setNear(float n);
        float far();
        void setFar(float f);
        virtual void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual Color getColor(Scene & scn, Ray & ray);
    };
}

#endif
