#include "light/PointLight.h"
#include "scene/Scene.h"

const vec3 PointLight::DEFAULT_FALL_OFF = vec3(0, 0, 1);
const vec3 PointLight::DEFAULT_POSITION = vec3(0, 0, 0);

float PointLight::calcBrightness(float dist) {
    return intensity / (fallOff.x + fallOff.y * dist + fallOff.z * dist * dist);
}

PointLight::PointLight() : Light() {
    setPosition(DEFAULT_POSITION);
    setFallOff(DEFAULT_FALL_OFF);
}

PointLight::PointLight(Color color) : Light(color) {
    setPosition(DEFAULT_POSITION);
    setFallOff(DEFAULT_FALL_OFF);
}

PointLight::PointLight(Color color, vec3 position) : Light(color) {
    setColor(color);
    setPosition(position);
    setFallOff(DEFAULT_FALL_OFF);
}

vec3 PointLight::getPosition() {
    return position;
}

void PointLight::setPosition(vec3 position) {
    this->position = position;
}

vec3 PointLight::getFallOff() {
    return fallOff;
}

void PointLight::setFallOff(vec3 fallOff) {
    this->fallOff = fallOff;
}

float PointLight::getBrightness(Scene & scene, Intersection & intersection, float t) {
    
    // Setup basic parameters
    vec3 diff = position - intersection.getPosition();
    float dist = sqrt(dot(diff, diff));
    
    // Check if the light cast shadow
    if (castShadow) {
        
        Ray ray = Ray(intersection.getPosition(), diff);
        ray.increment(intersection.getNormal()); // Must do to avoid floating point
        Intersection barrier = Intersection(ray);
        
        // Check shadow
        if (scene.getIntersection(ray, barrier, t) && barrier.getDistanceToOrigin() < dist) {
            return 0;
        }
    }
    
    // If not cast shadow or no shadow, return the normal brightness
    return calcBrightness(dist);
}

float PointLight::getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t) {
    return getBrightness(scene, intersection, t);
}

vec3 PointLight::getToLightDirection(Intersection & intersection) {
    return normalize(position - intersection.getPosition());
}

vector<vec3> PointLight::getToLightDirection(Intersection & intersection, int sampleAmount) {
    vector<vec3> r = vector<vec3>();
    r.push_back(getToLightDirection(intersection));
    return r;
}
