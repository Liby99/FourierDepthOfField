#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "engine/RenderEngine.h"
#include "util/Sampler.h"

class RayTracer : public RenderEngine {
protected:
    
    const static int DEFAULT_MAX_DEPTH = 3;
    const static int DEFAULT_SAMPLE_AMOUNT = 0;
    const static int DEFAULT_SAMPLING_METHOD = Sampler::RANDOM_SAMPLE;
    const static int DEFAULT_WEIGHTING_METHOD = Sampler::NO_WEIGHT;
    
    // Sampling parameters
    int sampleAmount;
    int maxDepth;
    
    // Sampling Methods
    int samplingMethod;
    int weightingMethod;
    
    void initiateSampling();
    
public:
    
    // Constructors
    RayTracer();
    RayTracer(int maxDepth);
    RayTracer(int maxDepth, int sampleAmount);
    RayTracer(Scene & scene);
    RayTracer(Scene & scene, int maxDepth);
    RayTracer(Scene & scene, int maxDepth, int sampleAmount);
    
    //
    int getMaxDepth();
    int getSampleAmount();
    void setMaxDepth(int maxDepth);
    void setSampleAmount(int sampleAmount);
    
    //
    int getSamplingMethod();
    int getWeightingMethod();
    void setSamplingMethod(int samplingMethod);
    void setWeightingMethod(int weightingMethod);
    
    //
    virtual Color getColor(Intersection & intersection, float t);
};

#endif
