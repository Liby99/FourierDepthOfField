#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "engine/Engine.h"
#include "engine/RaySample.h"
#include "scene/Scene.h"
#include "image/Image.h"
#include "utility/Sampler.h"

namespace recartyar {
    class PathTracer : public Engine {
    public:
        PathTracer();
        void render(Scene & scn, Image & img);
    protected:
        virtual void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual Color getColor(Scene & scn, Ray & ray);
        virtual Color getColor(Scene & scn, Intersection & itsct);
        virtual Light & getRandomLight(Scene & scn);
    };
}

#endif
