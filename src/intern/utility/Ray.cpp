#include "utility/Ray.h"

using namespace recartyar;

Ray::Ray() : Ray(vec3(), vec3(0, 0, 1)) {};

Ray::Ray(vec3 origin, vec3 direction) {
    this->origin = origin;
    this->direction = direction;
}

vec3 Ray::getPoint(float t) {
    return this->origin + t * this->direction;
}

void Ray::increment() {
    this->origin += this->direction * 0.0001f;
}
