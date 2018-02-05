#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include "scene/Scene.h"
#include "material/Material.h"

class RenderEngine {
protected:
    Scene * scene;
public:
    RenderEngine();
    RenderEngine(Scene & scene);
    virtual void setScene(Scene & scene);
    Scene & getScene();
    virtual Color getColor(Intersection & intersection, float t);
};

#endif
