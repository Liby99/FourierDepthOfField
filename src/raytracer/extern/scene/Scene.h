#ifndef SCENE_H
#define SCENE_H

#include "util/Color.h"
#include "util/Ray.h"
#include "util/Intersection.h"
#include "object/Object.h"
#include "material/Material.h"
#include "light/Light.h"

using namespace std;

class RenderEngine;

class Scene {
protected:
    
    // Global Variables
    Color background;
    RenderEngine * engine;
    vector<Object *> objects;
    vector<Light *> lights;
    
public:
    
    // Constructor and Destructors
    Scene();
    
    void setRenderEngine(RenderEngine & engine);
    
    // Background
    Color getBackgroundColor();
    void setBackgroundColor(Color color);
    
    // Light related getter and setter
    bool hasLight();
    unsigned int lightAmount();
    Light & getLight(int i);
    virtual void addLight(Light & light);
    
    // Object related getter and setter
    bool hasObject();
    unsigned int objectAmount();
    Object & getObject(int i);
    virtual void addObject(Object & object);
    
    // Intersection
    virtual bool getIntersection(Ray & ray, Intersection & intersection, float t);
    virtual Color getRayColor(Ray & ray, float t);
};

#endif
