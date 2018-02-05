#ifndef LUMINANCE_H
#define LUMINANCE_H

#include "material/Material.h"

class Luminance : public Material {
private:
    
    Color color;
    float intensity;
    
public:
    
    Luminance();
    Luminance(Color color);
    Luminance(Color color, float intensity);
    
    Color getColor();
    void setColor(Color color);
    
    float getIntensity();
    void setIntensity(float intensity);
    
    virtual Color emission();
};

#endif
