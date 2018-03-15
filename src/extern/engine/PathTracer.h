#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "engine/RenderEngine.h"
#include "scene/Scene.h"
#include "image/Image.h"
#include "utility/Sampler.h"

namespace recartyar {
    class PathTracer : public RenderEngine {
    public:
        int mSpp;
    protected:
        int currI, currJ, currK;
        float hw, hh;
    public:
        PathTracer();
        explicit PathTracer(int spp);
        int superSampling();
        void setSuperSampling(int spp);
    protected:
        void initiateGenerator(Scene & scn, Image & img) override;
        RaySample getNextSample(Scene & scn, Image & img) override;
        bool hasNextSample(Scene & scn, Image & img) override;
        Color getColor(Scene & scn, Intersection & itsct) override;
        Light & getRandomLight(Scene & scn);
    };
}

#endif
