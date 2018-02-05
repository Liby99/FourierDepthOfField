#ifndef METAL_H
#define METAL_H

#include "material/Material.h"

class Metal : public Material {
private:
    
    // Private metal tint color
    Color color;
    
public:
    
    // Constructor
    Metal();
    Metal(Color color);
    
    // Color getter and setter
    Color getColor();
    void setColor(Color color);
    
    // Virtual methods
    virtual pair<Ray, Color> generateSample(Intersection & intersection, vec2 sample);
    virtual Color computeReflection(Intersection & i, Ray & out);
    virtual vector<pair<Ray, Color>> reflection(Intersection & i, int amount);
    virtual Color emission();
};

#endif
