#include "object/Object.h"

using namespace fdof;

Object::Object() : material(nullptr), box(nullptr) {}

Object::~Object() {
    if (box) {
        delete box;
    }
}

bool Object::hasMaterial() {
    return material != nullptr;
}

void Object::setMaterial(Material & mtl) {
    this->material = &mtl;
}

Material & Object::getMaterial() {
    return *this->material;
}

BoundingBox & Object::getBoundingBox() {
    if (!box) {
        initiateBoundingBox();
    }
    return *box;
}

void Object::initiateBoundingBox() {

    // First check if the box exists
    if (box) {
        delete box;
    }

    // Then get the bounding vertices
    box = new BoundingBox();
    std::vector<vec3> bvs;
    getBoundingVertices(bvs);
    mat4 transf = transform.getTransform();
    for (int i = 0; i < bvs.size(); i++) {

        // Transform and update min max
        vec3 v = transformHomogenous(transf, bvs[i]);
        box->extend(v);
    }
}

bool Object::intersect(Ray & ray, Intersection & itsct) {
    Ray transfRay = ray.inverseTransform(transform.getTransform());
    if (updateIntersect(transfRay, itsct)) {
        itsct.transform(transform.getTransform());
        itsct.setObject(*this);
        return true;
    }
    else {
        return false;
    }
}

void Object::getBoundingVertices(std::vector<vec3> & bvs) {
    // Do nothing cause no vertex
}

bool Object::updateIntersect(Ray & ray, Intersection & itsct) const {
    return false;
}

vec3 Object::transformHomogenous(const mat4 & m, const vec3 & vertex) {
    vec4 v = m * vec4(vertex, 1);
    return vec3(v.x, v.y, v.z) / v.w;
}
