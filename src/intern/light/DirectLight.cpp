#include "light/DirectLight.h"

using namespace fdof;

DirectLight::DirectLight() : DirectLight(vec3(-1, -1, -1)) {}

DirectLight::DirectLight(vec3 dir) : Light(), direction(dir) {}

DirectLight::DirectLight(Color color, vec3 dir) : Light(color), direction(dir) {}

float DirectLight::getBrightness(Intersection & objItsct, Intersection & lgtItsct) {
    return 1;
}

vec3 DirectLight::getToLightDir(Intersection & itsct) {
    return -direction;
}
