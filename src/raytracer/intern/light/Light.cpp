#include "light/Light.h"

const Color Light::DEFAULT_COLOR = Color::WHITE;
const float Light::DEFAULT_INTENSITY = 1;
const bool Light::DEFAULT_CAST_SHADOW = true;

Light::Light() {
    setColor(DEFAULT_COLOR);
    setIntensity(DEFAULT_INTENSITY);
    setCastShadow(DEFAULT_CAST_SHADOW);
}

Light::Light(Color c) {
    setColor(c);
    setIntensity(DEFAULT_INTENSITY);
    setCastShadow(DEFAULT_CAST_SHADOW);
}

Color Light::getColor() {
    return color;
}

void Light::setColor(Color color) {
    this->color = color;
}

float Light::getIntensity() {
    return intensity;
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
}

bool Light::getCastShadow() {
    return castShadow;
}

void Light::setCastShadow(bool castShadow) {
    this->castShadow = castShadow;
}

float Light::getBrightness(Scene & scene, Intersection & intersection, float t) {
    return 0;
}

float Light::getBrightness(Scene & scene, Intersection & intersection, Ray & ray, float t) {
    return 0;
}

vec3 Light::getToLightDirection(Intersection & intersection) {
    return vec3(0, 0, 0);
}

vector<vec3> Light::getToLightDirection(Intersection & intersection, int sampleAmount) {
    return vector<vec3>();
}
