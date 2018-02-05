#include "object/Cloner.h"

bool Cloner::updateIntersect(Ray & ray, Intersection & intersection, float t) {
    bool result = false;
    for (int i = 0; i < instances.size(); i++) {
        if (instances[i]->intersect(ray, intersection, t)) {
            result = true;
        }
    }
    return result;
}

vec3 Cloner::sampleSurfacePointHelper(float t) {
    return instances[rand() % instances.size()]->sampleSurfacePoint(t);
}

Cloner::Cloner(Object & object) : Object() {
    this->object = &object;
    this->useSeparateMaterial = false;
}

void Cloner::enableSeparateMaterial() {
    useSeparateMaterial = true;
}

void Cloner::disableSeparateMaterial() {
    useSeparateMaterial = false;
}

void Cloner::setMaterial(Material & mtl) {
    Object::setMaterial(mtl);
}

void Cloner::setMaterial(int i, Material & mtl) {
    instances[i]->setMaterial(mtl);
}

void Cloner::setMaterial(vector<Material *> mtls) {
    for (int i = 0; i < instances.size(); i++) {
        setMaterial(i, *(mtls[i % mtls.size()]));
    }
}

bool Cloner::intersect(Ray & ray, Intersection & intersection, float t) {
    Ray transfRay = ray.inverseTransform(getTransformMatrix(t));
    if (updateIntersect(transfRay, intersection, t)) {
        intersection.transform(getTransformMatrix(t));
        if (!useSeparateMaterial) {
            intersection.setObject(*this);
        }
        return true;
    }
    else {
        return false;
    }
}
