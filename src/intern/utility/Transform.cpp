#include "utility/Transform.h"

using namespace recartyar;

Transform::Transform() : mPosition(vec3(0, 0, 0)), mRotation(vec3(0, 0, 0)), mScale(vec3(1, 1, 1)) {
    mCached = false;
}

void Transform::translate(vec3 t) {
    translate(mPosition + t);
}

void Transform::setPosition(vec3 p) {
    mCached = false;
    mPosition = p;
}

void Transform::scale(vec3 s) {
    setScale(mScale * s);
}

void Transform::setScale(vec3 s) {
    mCached = false;
    mScale = s;
}

void Transform::rotate(vec3 r) {
    setRotation(mRotation + r);
}

void Transform::setRotation(vec3 r) {
    mCached = false;
    mRotation = r;
}

vec3 Transform::position() {
    return mPosition;
}

vec3 Transform::rotation() {
    return mRotation;
}

vec3 Transform::scale() {
    return mScale;
}

mat4 Transform::getTransform() {
    if (!mCached) {
        mCache = getTranslateMatrix() * getRotateMatrix() * getScaleMatrix();
        mCached = true;
    }
    return mCache;
}

mat4 Transform::getTranslateMatrix() {
    return glm::translate(mat4(1.0f), mPosition);
}

mat4 Transform::getRotateXMatrix() {
    return glm::rotate(mat4(1.0f), mRotation.x, vec3(1, 0, 0));
}

mat4 Transform::getRotateYMatrix() {
    return glm::rotate(mat4(1.0f), mRotation.y, vec3(0, 1, 0));
}

mat4 Transform::getRotateZMatrix() {
    return glm::rotate(mat4(1.0f), mRotation.z, vec3(0, 0, 1));
}

mat4 Transform::getRotateMatrix() {
    return getRotateZMatrix() * getRotateYMatrix() * getRotateXMatrix();
}

mat4 Transform::getScaleMatrix() {
    return glm::scale(mat4(1.0f), mScale);
}
