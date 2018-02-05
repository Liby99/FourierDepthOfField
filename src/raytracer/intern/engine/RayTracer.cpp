#include "engine/Raytracer.h"

void RayTracer::initiateSampling() {
    setSamplingMethod(DEFAULT_SAMPLING_METHOD);
    setWeightingMethod(DEFAULT_WEIGHTING_METHOD);
}

RayTracer::RayTracer() : RayTracer(DEFAULT_MAX_DEPTH) {}

RayTracer::RayTracer(int maxDepth) : RayTracer(maxDepth, DEFAULT_SAMPLE_AMOUNT) {}

RayTracer::RayTracer(int maxDepth, int sampleAmount) : RenderEngine() {
    setMaxDepth(maxDepth);
    setSampleAmount(sampleAmount);
    initiateSampling();
}

RayTracer::RayTracer(Scene & scene) : RayTracer(scene, DEFAULT_MAX_DEPTH) {}

RayTracer::RayTracer(Scene & scene, int maxDepth) : RayTracer(scene, maxDepth, DEFAULT_SAMPLE_AMOUNT) {}

RayTracer::RayTracer(Scene & scene, int maxDepth, int sampleAmount) : RenderEngine(scene) {
    setMaxDepth(maxDepth);
    setSampleAmount(sampleAmount);
    initiateSampling();
}

int RayTracer::getMaxDepth() {
    return maxDepth;
}

int RayTracer::getSampleAmount() {
    return sampleAmount;
}

void RayTracer::setMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
}

void RayTracer::setSampleAmount(int sampleAmount) {
    this->sampleAmount = sampleAmount;
}

int RayTracer::getSamplingMethod() {
    return samplingMethod;
}

int RayTracer::getWeightingMethod() {
    return weightingMethod;
}

void RayTracer::setSamplingMethod(int samplingMethod) {
    this->samplingMethod = samplingMethod;
}

void RayTracer::setWeightingMethod(int weightingMethod) {
    this->weightingMethod = weightingMethod;
}

Color RayTracer::getColor(Intersection & intersection, float t) {
    
    // Prepare the variables
    Color color = Color::BLACK;
    
    if (intersection.getObject().hasMaterial()) {
        
        // Cache the material
        Material & mtl = intersection.getObject().getMaterial();
        vec3 normal = intersection.getNormal();
        
        // First add the emission
        color += mtl.emission();
        
        // Then calculate the reflection if the ray can recurse downward
        if (intersection.getRay().getDepth() < maxDepth) {
            vector<pair<Ray, Color>> reflections = mtl.reflection(intersection, sampleAmount);
            for (int i = 0; i < reflections.size(); i++) {
                color += scene->getRayColor(reflections[i].first, t) * reflections[i].second;
            }
        }
        
        // Then calculate the lighting
        for (int i = 0; i < scene->lightAmount(); i++) {
            
            // Sample to light direction
            Light & light = scene->getLight(i);
            
            vector<vec3> dirs = light.getToLightDirection(intersection, sampleAmount);
            
            // Check if there is greater than 1 sample
            if (dirs.size() > 0) {
                
                // Initiate the lighting color
                Color lighting = Color::BLACK;
                
                // Loop through all the sample directions
                for (int j = 0; j < dirs.size(); j++) {
                    
                    // Get the brightness from that direction
                    Ray toLight = Ray(intersection.getPosition(), dirs[j]);
                    float brightness = light.getBrightness(*scene, intersection, toLight, t);
                    if (brightness > 0.0f) {
                        
                        // If brightness is greater than 0, then calculate the reflectance on that
                        // direction
                        Color lc = light.getColor() * brightness;
                        float cosTheta = max(dot(dirs[j], normal), 0.0f);
                        Color ob = mtl.computeReflection(intersection, toLight) / dirs.size() * cosTheta;
                        lighting += lc * ob;
                    }
                }
                
                // Normalize the lighting color
                lighting /= dirs.size();
                color += lighting;
            }
        }
    }
    
    return color;
}
