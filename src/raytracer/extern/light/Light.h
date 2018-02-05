#ifndef LIGHT_H
#define LIGHT_H

#include "util/Transform.h"
#include "util/Color.h"
#include "util/Ray.h"
#include "util/Intersection.h"

#include <vector>

using namespace std;

class Scene;

class Light {
protected:
    
    const static Color DEFAULT_COLOR;
    const static float DEFAULT_INTENSITY;
    const static bool DEFAULT_CAST_SHADOW;
    
    // Private color
    Color color;
    float intensity;
    bool castShadow;
    
public:
    
    // Constructor
    Light();
    Light(Color c);
    
    // Color related setter getter
    virtual Color getColor();
    virtual void setColor(Color color);
    virtual float getIntensity();
    virtual void setIntensity(float intensity);
    virtual bool getCastShadow();
    virtual void setCastShadow(bool castShadow);
    
    // Illuminate
    virtual float getBrightness(Scene & scene, Intersection & intersection, float t);
    virtual float getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t);
    virtual vec3 getToLightDirection(Intersection & intersection);
    virtual vector<vec3> getToLightDirection(Intersection & intersection, int sampleAmount);
};

#endif
