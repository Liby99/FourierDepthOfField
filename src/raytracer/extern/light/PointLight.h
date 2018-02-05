#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light/Light.h"

using namespace std;

class PointLight : public Light {
protected:
    
    // Default Fall Off and position
    const static vec3 DEFAULT_POSITION;
    const static vec3 DEFAULT_FALL_OFF;
    
    // Basic Variables
    vec3 position;
    vec3 fallOff;
    
    // Helper method for getting brightness
    float calcBrightness(float distance) ;
    
public:
    
    // Constructor
    PointLight();
    PointLight(Color color);
    PointLight(Color color, vec3 position);
    
    // Position setter getter
    vec3 getPosition();
    void setPosition(vec3 position);
    
    // Fall Off related setter getter
    vec3 getFallOff();
    void setFallOff(vec3 fallOff);
    
    // Inherited brightness and tolight
    virtual float getBrightness(Scene & scene, Intersection & intersection, float t);
    virtual float getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t);
    virtual vec3 getToLightDirection(Intersection & intersection);
    virtual vector<vec3> getToLightDirection(Intersection & intersection, int sampleAmount);
};

#endif
