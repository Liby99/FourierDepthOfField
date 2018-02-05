#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "util/Transform.h"
#include "util/Ray.h"

class Object;

class Intersection {
private:
    
    // Reference to ray and object
    Ray * ray;
    Object * object;
    
    // Intersection parameters
    bool hitFlag;
    float t;
    vec3 position;
    vec3 normal;
    vec3 tangentU;
    vec3 tangentV;
    
public:
    
    // Constructor
    Intersection(Ray & ray);
    
    // Reference Getter and setter
    Object & getObject();
    void setObject(Object & object);
    Ray & getRay();
    void setRay(Ray & ray);
    
    // Parameter Getter and setter
    bool hit();
    void setHit(bool hit);
    float getT();
    void setT(float t);
    vec3 getPosition();
    void setPosition(vec3 position);
    vec3 getNormal();
    vec3 getTangentU();
    vec3 getTangentV();
    void setNormal(vec3 normal);
    void setTangentU(vec3 u);
    void setTangentV(vec3 v);
    
    float getDistanceToOrigin();
    bool needUpdate(float t);
    bool update(float t, vec3 position, vec3 normal);
    
    void transform(mat4 transform);
};

#endif
