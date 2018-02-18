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
        PathTracer();
        int superSampling();
        void setSuperSampling(int spp);
    protected:
        virtual void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual Color getColor(Scene & scn, Intersection & itsct);
        virtual Light & getRandomLight(Scene & scn);
    };
}

#endif
