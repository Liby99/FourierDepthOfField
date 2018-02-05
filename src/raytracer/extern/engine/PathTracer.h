#ifndef PATH_TRACER_H
#define PATH_TRACER_H

#include "engine/RenderEngine.h"
#include "util/Sampler.h"

class PathTracer : public RenderEngine {
protected:
    
    // Constants
    const static int DEFAULT_MAX_DEPTH = 5;
    
    // Private variables
    int maxDepth;
    
public:
    
    // Constructors
    PathTracer();
    PathTracer(int maxDepth);
    PathTracer(Scene & scene);
    PathTracer(Scene & scene, int maxDepth);
    
    //
    int getMaxDepth();
    void setMaxDepth(int maxDepth);
    
    //
    virtual Color getColor(Intersection & intersection, float t);
};

#endif
