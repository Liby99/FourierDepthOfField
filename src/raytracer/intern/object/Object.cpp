#include "object/Object.h"

#include <iostream>

const vec3 Object::DEFAULT_POSITION = vec3(0, 0, 0);
const vec3 Object::DEFAULT_SCALER = vec3(1, 1, 1);
const vec3 Object::DEFAULT_ROTATION = vec3(0, 0, 0);

vec3 transfHomogenous(mat4 matrix, vec3 vertex) {
    vec4 v = matrix * vec4(vertex, 1);
    return vec3(v.x, v.y, v.z) / v.w;
}

bool Object::updateIntersect(Ray & ray, Intersection & intersection, float t) {
    return false;
}

vector<vec3> Object::getBoundingVertices() {
    return vector<vec3>();
}

vec3 Object::sampleSurfacePointHelper(float t) {
    throw 100;
}

Object::Object() {
    setRotate(DEFAULT_ROTATION);
    setTranslate(DEFAULT_POSITION);
    setScale(DEFAULT_SCALER);
    box = nullptr;
    material = nullptr;
    transformed = false;
    surfaceArea = 0;
}

Object::~Object() {
    if (box) {
        delete box;
    }
}

bool Object::hasMaterial() {
    return material != nullptr;
}

Material & Object::getMaterial() {
    return *material;
}

void Object::setMaterial(Material & material) {
    this->material = &material;
}

vec3 Object::getRotation(float t) {
    return rotation.get(t);
}

vec3 Object::getScale(float t) {
    return scaler.get(t);
}

vec3 Object::getPosition(float t) {
    return position.get(t);
}

void Object::setRotate(vec3 rotation) {
    this->rotation.set(rotation);
    transformed = true;
}

void Object::rotate(vec3 rotation) {
    this->rotation.set([rotation] (vec3 & value) {
        value += rotation;
    });
    transformed = true;
}

void Object::rotateX(float degX) {
    this->rotation.set([degX] (vec3 & value) {
        value.x += degX;
    });
    transformed = true;
}

void Object::rotateY(float degY) {
    this->rotation.set([degY] (vec3 & value) {
        value.y += degY;
    });
    transformed = true;
}

void Object::rotateZ(float degZ) {
    this->rotation.set([degZ] (vec3 & value) {
        value.z += degZ;
    });
    transformed = true;
}

void Object::rotate(vec3 rotation, int t) {
    this->rotation.set(t, [rotation] (vec3 & value) {
        value += rotation;
    });
    transformed = true;
}

void Object::rotateX(float degX, int t) {
    this->rotation.set(t, [degX] (vec3 & value) {
        value.x += degX;
    });
    transformed = true;
}

void Object::rotateY(float degY, int t) {
    this->rotation.set(t, [degY] (vec3 & value) {
        value.y += degY;
    });
    transformed = true;
}

void Object::rotateZ(float degZ, int t) {
    this->rotation.set(t, [degZ] (vec3 & value) {
        value.z += degZ;
    });
    transformed = true;
}

void Object::setTranslate(vec3 translate) {
    this->position.set(translate);
    transformed = true;
}

void Object::translate(vec3 translate) {
    this->position.set([translate] (vec3 & value) {
        value += translate;
    });
    transformed = true;
}

void Object::translateX(float x) {
    this->position.set([x] (vec3 & value) {
        value.x += x;
    });
    transformed = true;
}

void Object::translateY(float y) {
    this->position.set([y] (vec3 & value) {
        value.y += y;
    });
    transformed = true;
}

void Object::translateZ(float z) {
    this->position.set([z] (vec3 & value) {
        value.z += z;
    });
    transformed = true;
}

void Object::translate(vec3 translate, int t) {
    this->position.set(t, [translate] (vec3 & value) {
        value += translate;
    });
    transformed = true;
}

void Object::translateX(float x, int t) {
    this->position.set(t, [x] (vec3 & value) {
        value.x += x;
    });
    transformed = true;
}

void Object::translateY(float y, int t) {
    this->position.set(t, [y] (vec3 & value) {
        value.y += y;
    });
    transformed = true;
}

void Object::translateZ(float z, int t) {
    this->position.set(t, [z] (vec3 & value) {
        value.z += z;
    });
    transformed = true;
}

void Object::setScale(vec3 scaler) {
    this->scaler.set(scaler);
    transformed = true;
}

void Object::scale(vec3 scaler) {
    this->scaler.set([scaler] (vec3 & value) {
        value *= scaler;
    });
    transformed = true;
}

void Object::scaleX(float scaleX) {
    this->scaler.set([scaleX] (vec3 & value) {
        value.x *= scaleX;
    });
    transformed = true;
}

void Object::scaleY(float scaleY) {
    this->scaler.set([scaleY] (vec3 & value) {
        value.y *= scaleY;
    });
    transformed = true;
}

void Object::scaleZ(float scaleZ) {
    this->scaler.set([scaleZ] (vec3 & value) {
        value.z *= scaleZ;
    });
    transformed = true;
}

void Object::scale(vec3 scaler, int t) {
    this->scaler.set(t, [scaler] (vec3 & value) {
        value *= scaler;
    });
    transformed = true;
}

void Object::scaleX(float scaleX, int t) {
    this->scaler.set(t, [scaleX] (vec3 & value) {
        value.x *= scaleX;
    });
    transformed = true;
}

void Object::scaleY(float scaleY, int t) {
    this->scaler.set(t, [scaleY] (vec3 & value) {
        value.y *= scaleY;
    });
    transformed = true;
}

void Object::scaleZ(float scaleZ, int t) {
    this->scaler.set(t, [scaleZ] (vec3 & value) {
        value.z *= scaleZ;
    });
    transformed = true;
}

mat4 Object::getTransformMatrix(float t) {
    vec3 sc = this->scaler.get(t);
    vec3 tr = this->position.get(t);
    vec3 ro = this->rotation.get(t);
    mat4 scale = Transform::scale(sc.x, sc.y, sc.z);
    mat4 translate = Transform::translate(tr.x, tr.y, tr.z);
    mat4 rotationX = Transform::rotate(ro.x, vec3(1, 0, 0));
    mat4 rotationY = Transform::rotate(ro.y, vec3(0, 1, 0));
    mat4 rotationZ = Transform::rotate(ro.z, vec3(0, 0, 1));
    return translate * rotationZ * rotationY * rotationX * scale;
}

vec3 Object::sampleSurfacePoint(float t) {
    vec3 p = sampleSurfacePointHelper(t);
    mat4 m = getTransformMatrix(t);
    return transfHomogenous(m, p);
}

BoundingBox Object::getBoundingBox(float t) {
    
    if (!box || transformed) {
        
        // Get all the vertices (approximatly 8) to find the bounding box
        vector<vec3> vertices = getBoundingVertices();
        
        // Check if the vector is empty
        if (vertices.empty()) {
            
            // If empty then return the empty box
            return *box;
        }
        else {
            
            box = new BoundingBox();
            
            if (transformed) {
            
                // First cache the matrix
                mat4 m = getTransformMatrix(t);
                
                // Iterate through
                for (int i = 0; i < vertices.size(); i++) {
                    
                    // Transform and update min max
                    vec3 v = transfHomogenous(m, vertices[i]);
                    box->extend(v);
                }
            }
            else {
                
                // If not transformed then directly extend v
                for (int i = 0; i < vertices.size(); i++) {
                    box->extend(vertices[i]);
                }
            }
            
            // Return the box
            return *box;
        }
    }
    else {
        return *box;
    }
}

bool Object::intersect(Ray & ray, Intersection & intersection, float t) {
    Ray transfRay = ray.inverseTransform(getTransformMatrix(t));
    if (updateIntersect(transfRay, intersection, t)) {
        intersection.transform(getTransformMatrix(t));
        intersection.setObject(*this);
        return true;
    }
    else {
        return false;
    }
}
