#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "light/PointLight.h"

using namespace std;

class SpotLight : public PointLight {
protected:
    
    // Constant default value
    const static vec3 DEFAULT_FALL_OFF;
    const static vec3 DEFAULT_TARGET;
    const static float DEFAULT_ANGLE;
    
    //
    vec3 target;
    float angle;
    
public:
    
    // Constructors
    SpotLight();
    SpotLight(Color color, vec3 position, vec3 target, float angle);
    
    // Basic getter and setter
    vec3 getPosition();
    void setPosition(vec3 position);
    vec3 getTarget();
    void setTarget(vec3 target);
    float getAngle();
    void setAngle(float angle);
    
    // Illuminate
    virtual float getBrightness(Scene & scene, Intersection & intersection, float t);
    virtual float getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t);
    virtual vec3 getToLightDirection(Intersection & intersection);
    virtual vector<vec3> getToLightDirection(Intersection & intersection, int sampleAmount);
};

#endif
