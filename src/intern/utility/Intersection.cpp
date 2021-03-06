#include "utility/Intersection.h"

using namespace fdof;

Intersection::Intersection(Ray & ray) : ray(&ray), object(nullptr), hit(false) {}

bool Intersection::hasObject() {
    return object != nullptr;
}

Object & Intersection::getObject() {
    return *object;
}

void Intersection::setObject(Object & object) {
    this->object = &object;
}

Ray & Intersection::getRay() {
    return *ray;
}

void Intersection::setRay(Ray & ray) {
    this->ray = &ray;
}

float Intersection::distToOrigin() {
    return glm::length(position - ray->origin);
}

bool Intersection::needUpdate(float t) {
    return !hit || t < this->t;
}

bool Intersection::update(float t, vec3 position, vec3 normal) {
    if (needUpdate(t)) {
        this->t = t;
        this->position = position;
        this->normal = normal;
        this->hit = true;
        return true;
    }
    return false;
}

void Intersection::transform(mat4 transf) {
    vec4 nPos = transf * vec4(position, 1);
    vec4 nNorm = transpose(inverse(transf)) * vec4(normal, 0);
    position = vec3(nPos) / nPos.w;
    normal = normalize(vec3(nNorm));
    // t = distToOrigin();
}
