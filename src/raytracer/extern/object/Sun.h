#ifndef SUN_H
#define SUN_H

#include "object/Object.h"

class Sun : public Object {
protected:
    
    vec3 direction;
    float angle;
    
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    
public:
    
    const static vec3 DEFAULT_DIRECTION;
    const static float DEFAULT_ANGLE;
    
    Sun();
    Sun(vec3 direction, float angle);
    
    vec3 getDirection();
    void setDirection(vec3 direction);
    
    float getAngle();
    void setAngle(float angle);
};

#endif
