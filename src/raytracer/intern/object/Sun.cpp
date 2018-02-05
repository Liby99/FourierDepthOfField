#include "object/Sun.h"

#include <iostream>

using namespace std;

const vec3 Sun::DEFAULT_DIRECTION = vec3(1, 1, 1);
const float Sun::DEFAULT_ANGLE = 5;

bool Sun::updateIntersect(Ray & ray, Intersection & intersection, float t) {
    vec3 raydir = ray.getDirection();
    if (acos(dot(raydir, direction)) < glm::radians(angle / 2)) {
        return intersection.update(MAXFLOAT, ray.getPoint(MAXFLOAT), -raydir);
    }
    else {
        return false;
    }
}

Sun::Sun() : Sun(DEFAULT_DIRECTION, DEFAULT_ANGLE) {}

Sun::Sun(vec3 direction, float angle) {
    setDirection(direction);
    setAngle(angle);
}

vec3 Sun::getDirection() {
    return direction;
}

void Sun::setDirection(vec3 direction) {
    this->direction = normalize(direction);
}

float Sun::getAngle() {
    return angle;
}

void Sun::setAngle(float angle) {
    this->angle = angle;
}
