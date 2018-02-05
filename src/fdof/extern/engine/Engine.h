#ifndef ENGINE_H
#define ENGINE_H

#include "scene/Scene.h"
#include "image/Image.h"

namespace fdof {
    class Engine {
    public:
        int width;
        int height;
        Engine();
        Engine(int width, int height);
        virtual Color getColor(Intersection & itsct);
        virtual Image render(Scene & scn);
    };
}

#endif
