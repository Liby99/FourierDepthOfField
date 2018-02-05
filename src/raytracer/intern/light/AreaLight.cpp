#include "light/AreaLight.h"
#include "scene/Scene.h"

void AreaLight::initiateLuminance() {
    initiateLuminance(Color::WHITE);
}

void AreaLight::initiateLuminance(Color color) {
    if (!material) {
        material = new Luminance(color, 1);
    }
}

AreaLight::AreaLight() : Light(), InstanceObject() {
    initiateLuminance();
}

AreaLight::AreaLight(Object & object) : Light(), InstanceObject(object) {
    initiateLuminance();
}

AreaLight::AreaLight(Object & object, Color color) : Light(), InstanceObject(object) {
    initiateLuminance(color);
}

Color AreaLight::getColor() {
    return material->emission();
}

void AreaLight::setColor(Color color) {
    Luminance * lum = static_cast<Luminance *>(material);
    lum->setColor(color);
}

float AreaLight::getIntensity() {
    Luminance * lum = static_cast<Luminance *>(material);
    return lum->getIntensity();
}

void AreaLight::setIntensity(float intensity) {
    Luminance * lum = static_cast<Luminance *>(material);
    lum->setIntensity(intensity);
}

float AreaLight::getBrightness(Scene & scene, Intersection & intersection, float t) {
    Ray toLight = Ray(intersection.getPosition(), getToLightDirection(intersection));
    toLight.increment(intersection.getNormal());
    return getBrightness(scene, intersection, toLight, t);
}

float AreaLight::getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t) {
    
    Intersection lgtits = Intersection(ray);
    if (InstanceObject::intersect(ray, lgtits, t)) {
        
        vec3 pos = lgtits.getPosition();
        vec3 origin = intersection.getPosition();
        vec3 diff = pos - origin;
        float dist = sqrt(dot(diff, diff));
        
        if (castShadow) {
            
            Intersection barrier = Intersection(ray);
            bool itsct = scene.getIntersection(ray, barrier, t);
            
            AreaLight * itsctlgt = dynamic_cast<AreaLight *>(&(barrier.getObject()));
            if (itsct && itsctlgt != this && barrier.getDistanceToOrigin() < dist) {
                return 0;
            }
        }
        
        Luminance * lum = static_cast<Luminance *>(material);
        return lum->getIntensity() / (dist * dist);
    }
    else {
        return 0;
    }
}

vec3 AreaLight::getToLightDirection(Intersection & intersection) {
    return sampleSurfacePoint(0) - intersection.getPosition();
}
