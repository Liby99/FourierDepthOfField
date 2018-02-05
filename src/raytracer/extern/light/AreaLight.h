#ifndef AREA_LIGHT_H
#define AREA_LIGHT_H

#include "light/Light.h"
#include "material/Luminance.h"
#include "object/InstanceObject.h"

class AreaLight : public Light, public InstanceObject {
private:
    
    using Object::setMaterial;
    
protected:
    
    void initiateLuminance();
    void initiateLuminance(Color color);
    
public:
    
    AreaLight();
    AreaLight(Object & object);
    AreaLight(Object & object, Color color);
    
    virtual Color getColor();
    virtual void setColor(Color color);
    virtual float getIntensity();
    virtual void setIntensity(float intensity);
    
    virtual float getBrightness(Scene & scene, Intersection & intersection, float t);
    virtual float getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t);
    virtual vec3 getToLightDirection(Intersection & intersection);
};

#endif
