#include "light/DirectionalLight.h"
#include "scene/Scene.h"

const vec3 DirectionalLight::DEFAULT_DIRECTION = vec3(-1, -1, -1);

DirectionalLight::DirectionalLight() : Light() {
    setDirection(DEFAULT_DIRECTION);
}

DirectionalLight::DirectionalLight(Color color) : Light(color) {
    setDirection(DEFAULT_DIRECTION);
}

DirectionalLight::DirectionalLight(Color color, vec3 direction) : Light(color) {
    setDirection(direction);
}

vec3 DirectionalLight::getDirection() {
    return direction;
}

void DirectionalLight::setDirection(vec3 direction) {
    this->direction = normalize(direction);
}

float DirectionalLight::getBrightness(Scene & scene, Intersection & intersection, float t) {
    
    // Chcek cast shadow
    if (castShadow) {
        
        Ray ray = Ray(intersection.getPosition(), -direction);
        ray.increment(intersection.getNormal()); // Must do to avoid floating point
        Intersection barrier = Intersection(ray);
        
        // Check shadow
        if (scene.getIntersection(ray, barrier, t)) {
            return 0;
        }
    }
    
    // If not cast shadow or no shadow, return the normal brightness
    return intensity;
}

float DirectionalLight::getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t) {
    return getBrightness(scene, intersection, t);
}

vec3 DirectionalLight::getToLightDirection(Intersection & intersection) {
    return -direction;
}

vector<vec3> DirectionalLight::getToLightDirection(Intersection & intersection, int sampleAmount) {
    vector<vec3> r = vector<vec3>();
    r.push_back(getToLightDirection(intersection));
    return r;
}
