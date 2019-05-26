#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "scene/Scene.h"
#include "image/Image.h"
#include "engine/RaySample.h"

namespace fdof {
    class RenderEngine {
    public:
        int mDepth;
        RenderEngine();
        int depth();
        void setDepth(int depth);
        virtual void render(Scene & scn, Image & img);
    protected:
        virtual void preProcessing(Scene & scn, Image & img);
        virtual void renderWithSample(Scene & scn, Image & img);
        virtual void postProcessing(Scene & scn, Image & img);
        virtual void initiateGenerator(Scene & scn, Image & img);
        virtual RaySample getNextSample(Scene & scn, Image & img);
        virtual bool hasNextSample(Scene & scn, Image & img);
        virtual Color getColor(Scene & scn, Ray & ray);
        virtual Color getColor(Scene & scn, Intersection & itsct);
    };
}

#endif
