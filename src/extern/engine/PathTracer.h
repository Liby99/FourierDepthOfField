#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "engine/Engine.h"
#include "scene/Scene.h"
#include "image/Image.h"

namespace recartyar {
    class PathTracer : public Engine {
    public:
        PathTracer();
        void render(Scene & scn, Image & img);
    protected:
        Color getColor(Scene & scn, Ray & ray);
        Color getColor(Scene & scn, Intersection & itsct);
    };
}

#endif
