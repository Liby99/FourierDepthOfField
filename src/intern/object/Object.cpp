#include "object/Object.h"

using namespace recartyar;

Object::Object() : material(nullptr) {}

bool Object::hasMaterial() {
    return material != nullptr;
}

void Object::setMaterial(Material & mtl) {
    this->material = &mtl;
}

Material & Object::getMaterial() {
    return *this->material;
}

bool Object::intersect(Ray & ray, Intersection & itsct) {
    return false;
}
