#ifndef ASHIKHMIN_H
#define ASHIKHMIN_H

#include "material/Material.h"
#include "util/Sampler.h"

class Ashikhmin : public Material {
private:
    
    // Initialize constants
    const static float DEFAULT_DIFFUSE_LEVEL;
    const static Color DEFAULT_DIFFUSE_COLOR;
    const static float DEFAULT_SPECULAR_LEVEL;
    const static Color DEFAULT_SPECULAR_COLOR;
    const static float DEFAULT_ROUGHNESS;
    
    // Sampler Related
    int sampleMethod;
    int weightMethod;
    
    // Ashikhmin basic variables
    float diffuseLevel;
    Color diffuseColor;
    float specularLevel;
    Color specularColor;
    float roughnessU;
    float roughnessV;
    
public:
    
    Ashikhmin();
    
    void setSampleMethod(int sm);
    void setWeightMethod(int wm);
    
    void setDiffuseLevel(float level);
    float getDiffuseLevel();
    
    void setDiffuseColor(Color color);
    Color getDiffuseColor();
    
    void setSpecularLevel(float level);
    float getSpecularLevel();
    
    void setSpecularColor(Color color);
    Color getSpecularColor();
    
    void setRoughness(float u, float v);
    void setRoughnessU(float u);
    void setRoughnessV(float v);
    float getRoughnessU();
    float getRoughnessV();
    
    virtual pair<Ray, Color> generateSample(Intersection & intersection, vec2 sample);
    virtual Color computeReflection(Intersection & i, Ray & out);
    virtual Color emission();
};

#endif
