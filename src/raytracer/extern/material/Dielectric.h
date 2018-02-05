#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material/Material.h"

class Dielectric : public Material {
private:
    
    const static float DEFAULT_IOR;
    const static float DEFAULT_ABSORPTION_COEF;
    const static Color DEFAULT_ABSORPTION_COLOR;
    const static Color DEFAULT_SPECULAR_COLOR;
    
    float ior;
    float absorptionCoef;
    Color absorptionColor;
    Color specularColor;
    
public:
    
    const static float AIR_IOR;
    const static float WATER_IOR;
    const static float ICE_IOR;
    const static float GLASS_IOR;
    const static float DIAMOND_IOR;
    
    Dielectric();
    
    float getIor();
    void setIor(float ior);
    
    float getAbsorptionCoef();
    void setAbsorptionCoef(float coef);
    
    Color getAbsorptionColor();
    void setAbsorptionColor(Color c);
    
    Color getSpecularColor();
    void setSpecularColor(Color c);
    
    virtual pair<Ray, Color> generateSample(Intersection & intersection, vec2 sample);
    // virtual Color computeReflection(Intersection & i, Ray & out);
};

#endif
