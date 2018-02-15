#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "scene/Camera.h"
#include "light/Light.h"
#include "object/Object.h"
#include "utility/Intersection.h"
#include "utility/Ray.h"
#include "utility/Color.h"

namespace recartyar {
    class Scene {
    private:
        Color background;
        Camera camera;
        std::vector<Light *> lights;
        std::vector<Object *> objects;
    public:
        Scene();
        
        void setBackground(Color & color);
        Color & getBackground();
        
        Camera & getCamera();
        int lightCount();
        void addLight(Light & light);
        Light & getLight(int i);
        int objectCount();
        void addObject(Object & object);
        Object & getObject(int i);
        
        bool intersect(Ray & ray, Intersection & itsct);
    };
}

#endif
