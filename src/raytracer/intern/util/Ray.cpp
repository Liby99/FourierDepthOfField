#include "util/Ray.h"
#include "scene/Scene.h"

const float Ray::INCREMENT = 0.0001;

Ray::Ray() {
    setDepth(0);
    setInside(false);
}

Ray::Ray(vec3 origin, vec3 direction) : Ray(origin, direction, 0) {}

Ray::Ray(vec3 origin, vec3 direction, int depth) : Ray(origin, direction, depth, false) {}

Ray::Ray(vec3 origin, vec3 direction, int depth, bool inside) {
    setOrigin(origin);
    setDirection(direction);
    setDepth(depth);
    setInside(inside);
}

vec3 Ray::getOrigin() {
    return origin;
}

void Ray::setOrigin(vec3 origin) {
    this->origin = origin;
}

vec3 Ray::getDirection() {
    return direction;
}

void Ray::setDirection(vec3 direction) {
    this->direction = normalize(direction);
}

int Ray::getDepth() {
    return depth;
}

void Ray::setDepth(int depth) {
    this->depth = depth;
}

bool Ray::isInside() {
    return inside;
}

void Ray::setInside(bool inside) {
    this->inside = inside;
}

void Ray::increment() {
    increment(direction);
}

void Ray::increment(vec3 direction) {
    origin += INCREMENT * direction;
}

vec3 Ray::getPoint(float t) {
    return origin + t * direction;
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
