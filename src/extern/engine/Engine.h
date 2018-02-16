#ifndef ENGINE_H
#define ENGINE_H

#include "scene/Scene.h"
#include "image/Image.h"

namespace recartyar {
    class Engine {
    public:
        Engine();
        void render(Scene & scn, Image & img);
    };
}

#endif
