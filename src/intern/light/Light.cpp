#include "light/Light.h"

using namespace fdof;

Light::Light() : Light(Color(1, 1, 1)) {}

Light::Light(Color color) : color(color), intensity(1) {}

Color Light::getColor(Intersection & objItsct, Intersection & lgtItsct) {
    return color * getBrightness(objItsct, lgtItsct) * intensity;
}

float Light::getBrightness(Intersection & objItsct, Intersection & lgtItsct) {
    return 0;
}

vec3 Light::getToLightDir(Intersection & itsct) {
    return vec3(0, 0, 0);
}
