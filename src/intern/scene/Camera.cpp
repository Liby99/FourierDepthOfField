#include "scene/Camera.h"

using namespace recartyar;

Camera::Camera() : Camera(vec3(0, 0, 1), vec3(0, 0, 0)) {}

Camera::Camera(vec3 position, vec3 target) : mPosition(position), mTarget(target), mUp(vec3(0, 1, 0)),
    mAspect(16.0f / 9.0f), mFovy(glm::radians(60.0f)), mFocalDistance(1.0f), mAperture(0.01f) {};

vec3 Camera::position() const {
    return mPosition;
}

void Camera::setPosition(vec3 p) {
    mPosition = p;
}

vec3 Camera::target() const {
    return mTarget;
}

void Camera::setTarget(vec3 t) {
    mTarget = t;
}

float Camera::aspect() const {
    return mAspect;
}

void Camera::setAspect(float a) {
    mAspect = a;
}

float Camera::fovy() const {
    return mFovy;
}

void Camera::setFovy(float f) {
    mFovy = f;
}

float Camera::focalDistance() const {
    return mFocalDistance;
}

void Camera::setFocalDistance(float f) {
    mFocalDistance = f;
}

float Camera::aperture() const {
    return mAperture;
}

void Camera::setAperture(float a) {
    mAperture = a;
}

Ray Camera::getRay(const vec2 & scsp) const {
    return getRay(scsp, vec2(0, 0));
}

Ray Camera::getRay(const vec2 & scsp, const vec2 & apsp) const {
    
    // Setup camera variables
    vec3 w = glm::normalize(mTarget - mPosition);
    vec3 u = glm::normalize(glm::cross(w, mUp));
    vec3 v = glm::cross(w, u);

    // Cached uniform variables
    float b = -tan(mFovy / 2);
    float a = b * mAspect;

    // Calculate start
    vec3 s = mPosition;
    s += mAperture * (u * apsp.x + v * apsp.y);

    // Calculate direction
    vec3 d = glm::normalize(mPosition - s + mFocalDistance * glm::normalize(a * scsp.x * u + b * scsp.y * v + w));

    // Return the ray
    return Ray(s, d);
}
