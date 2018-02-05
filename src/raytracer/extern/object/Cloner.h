#ifndef CLONER_H
#define CLONER_H

#include "object/InstanceObject.h"

class Cloner : public Object {
protected:
    
    Object * object;
    vector<InstanceObject *> instances;
    
    bool useSeparateMaterial;
    
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vec3 sampleSurfacePointHelper(float t);
    
public:
    
    Cloner(Object & object);
    
    void enableSeparateMaterial();
    void disableSeparateMaterial();
    void setMaterial(Material & mtl);
    void setMaterial(int i, Material & mtl);
    void setMaterial(vector<Material *> mtls);
    
    virtual bool intersect(Ray & ray, Intersection & intersection, float t);
};

#endif
