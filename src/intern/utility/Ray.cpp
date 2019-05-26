#include "utility/Ray.h"

using namespace fdof;

Ray::Ray() : Ray(vec3(), vec3(0, 0, 1)) {};

Ray::Ray(vec3 origin, vec3 direction) : origin(origin), direction(direction), depth(0) {}

vec3 Ray::getPoint(float t) {
    return this->origin + t * this->direction;
}

void Ray::increment() {
    this->origin += this->direction * 0.0001f;
}

Ray Ray::transform(mat4 transf) {
    vec4 o = transf * vec4(origin, 1);
    vec3 no = vec3(o) / o.w;
    vec3 nd = vec3(transf * vec4(direction, 0));
    return Ray(no, nd);
}

Ray Ray::inverseTransform(mat4 transf) {
    return transform(inverse(transf));
}
