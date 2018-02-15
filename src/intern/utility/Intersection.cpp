#include "utility/Intersection.h"

using namespace recartyar;

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
    return t;
}

bool Intersection::update(float t, glm::vec3 position, glm::vec3 normal) {
    if (!hit || t < this->t) {
        this->t = t;
        this->position = position;
        this->normal = normal;
    }
}
