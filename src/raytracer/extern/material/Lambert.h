#ifndef LAMBERT_H
#define LAMBERT_H

#include "material/Material.h"
#include "util/Sampler.h"

class Lambert : public Material {
private:
    
    Color color;
    
public:
    
    // Constructor
    Lambert();
    Lambert(Color color);
    
    void setColor(Color color);
    Color getColor();
    
    // Virtual methods
    virtual pair<Ray, Color> generateSample(Intersection & intersection, vec2 sample);
    virtual Color computeReflection(Intersection & i, Ray & out);
    virtual Color emission();
};

#endif
