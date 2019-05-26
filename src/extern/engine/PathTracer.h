#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "engine/RenderEngine.h"
#include "scene/Scene.h"
#include "image/Image.h"
#include "utility/Sampler.h"

namespace fdof {
    class PathTracer : public RenderEngine {
    public:
        int mSpp;
    protected:
        int currI, currJ, currK;
        float hw, hh;
    public:
        PathTracer();
        explicit PathTracer(int spp);
        int superSampling() const;
        void setSuperSampling(int spp);
    protected:
        void initiateGenerator(Scene & scn, Image & img) override;
        RaySample getNextSample(Scene & scn, Image & img) override;
        bool hasNextSample(Scene & scn, Image & img) const override;
        Color getColor(Scene & scn, Intersection & itsct) const override;
        Light & getRandomLight(Scene & scn) const;
    };
}

#endif
