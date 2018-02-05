#include "utility/Ray.h"

using namespace fdof;

Ray::Ray() : Ray(glm::vec3(), glm::vec3(0, 0, 1)) {};

Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
    this->origin = origin;
    this->direction = direction;
}

glm::vec3 Ray::getPoint(float t) {
    return this->origin + t * this->direction;
}

void Ray::increment() {
    this->origin += this->direction * 0.0001f;
}
