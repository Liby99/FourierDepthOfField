#include "object/InstanceObject.h"

bool InstanceObject::updateIntersect(Ray & ray, Intersection & intersection, float t) {
    if (object) return object->intersect(ray, intersection, t);
    else return false;
}

vector<vec3> InstanceObject::getBoundingVertices() {
    if (object) return object->getBoundingBox(0).getBoundingVertices();
    else return vector<vec3>();
}

vec3 InstanceObject::sampleSurfacePointHelper(float t) {
    return object->sampleSurfacePoint(t);
}

InstanceObject::InstanceObject() : Object() {}

InstanceObject::InstanceObject(Object & object) : Object() {
    setObject(object);
    surfaceArea = object.surfaceArea;
}

Object & InstanceObject::getObject() {
    return *object;
}

void InstanceObject::setObject(Object & object) {
    this->object = &object;
}
