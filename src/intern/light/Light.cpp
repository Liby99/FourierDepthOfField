#include "light/Light.h"

using namespace recartyar;

Light::Light() : Light(Color(1, 1, 1)) {}

Light::Light(Color color) : color(color), intensity(1) {}

bool Light::intersect(Ray & ray, Intersection & itsct) {
    return false;
}
