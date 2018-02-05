#include "object/CircularCloner.h"

void CircularCloner::retransform(float t) {
    float r = radius.get(t);
    float step = 360.0f / count;
    for (int i = 0; i < count; i++) {
        float angle = step * i;
        float rad = glm::radians(angle);
        vec3 position = vec3(cos(rad) * r, 0, sin(rad) * r);
        instances[i]->setTranslate(position);
    }
}

void CircularCloner::reconstruct() {
    float r = this->radius.get(0);
    instances.clear();
    float step = 360.0f / count;
    for (int i = 0; i < count; i++) {
        float angle = step * i;
        float rad = glm::radians(angle);
        vec3 position = vec3(cos(rad) * r, 0, sin(rad) * r);
        InstanceObject * instance = new InstanceObject(*object);
        instance->setTranslate(position);
        instance->rotateY(-angle);
        instances.push_back(instance);
    }
}

CircularCloner::CircularCloner(Object & object) : CircularCloner(object, 1, 5) {}

CircularCloner::CircularCloner(Object & object, float radius, int count) : Cloner(object) {
    this->radius.set(radius);
    this->count = count;
    reconstruct();
}

float CircularCloner::getRadius(float t) {
    return this->radius.get(t);
}

void CircularCloner::setRadius(float radius) {
    this->radius.set(radius);
}

void CircularCloner::setRadius(float radius, int t) {
    this->radius.set(t, radius);
}

int CircularCloner::getCount() {
    return count;
}

void CircularCloner::setCount(int count) {
    this->count = count;
    reconstruct();
}

bool CircularCloner::intersect(Ray & ray, Intersection & intersection, float t) {
    retransform(t);
    Cloner::intersect(ray, intersection, t);
}
