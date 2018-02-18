#include "scene/Camera.h"

using namespace recartyar;

Camera::Camera() : Camera(vec3(0, 0, 1), vec3(0, 0, 0)) {}

Camera::Camera(vec3 position, vec3 target) : position(position), target(target), up(vec3(0, 1, 0)),
    aspect(16.0f / 9.0f), fovy(glm::radians(60.0f)), focalDistance(1.0f), aperture(0.01f) {};

Ray Camera::getRay(const vec2 & screenSample) {
    return getRay(screenSample, vec2(0, 0));
}

Ray Camera::getRay(const vec2 & screenSample, const vec2 & apertureSample) {
    
    // Setup camera variables
    vec3 w = glm::normalize(target - position);
    vec3 u = glm::normalize(glm::cross(w, up));
    vec3 v = glm::cross(w, u);

    // Cached uniform variables
    float b = -tan(fovy / 2);
    float a = b * aspect;

    // Calculate start
    vec3 start = position;
    start += aperture * (u * apertureSample.x + v * apertureSample.y);

    // Calculate direction
    vec3 dir = glm::normalize(position - start + focalDistance * glm::normalize(a * screenSample.x * u + b * screenSample.y * v + w));

    // Return the ray
    return Ray(start, dir);
}
