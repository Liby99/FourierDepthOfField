#include "utility/Ray.h"

using namespace recartyar;

Ray::Ray() : Ray(vec3(), vec3(0, 0, 1)) {};

Ray::Ray(vec3 origin, vec3 direction) : origin(origin), direction(direction), depth(0) {}

vec3 Ray::getPoint(float t) {
    return this->origin + t * this->direction;
}

void Ray::increment() {
    this->origin += this->direction * 0.0001f;
}
