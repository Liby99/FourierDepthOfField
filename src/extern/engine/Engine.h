#ifndef ENGINE_H
#define ENGINE_H

#include "scene/Scene.h"
#include "image/Image.h"
#include "engine/RaySample.h"

namespace recartyar {
    class Engine {
    public:
        int mDepth;
        Engine();
        int depth();
        void setDepth(int depth);
        void render(Scene & scn, Image & img);
    protected:
        virtual void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples);
        virtual Color getColor(Scene & scn, Ray & ray);
        virtual Color getColor(Scene & scn, Intersection & itsct);
    };
}

#endif
