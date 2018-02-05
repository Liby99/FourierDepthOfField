#include "scene/Camera.h"

using namespace fdof;

Camera::Camera() : Camera(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0)) {}

Camera::Camera(glm::vec3 position, glm::vec3 target) :
    position(position), target(target), up(glm::vec3(0, 1, 0)),
    aspect(16.0f / 9.0f), fovy(glm::radians(60.0f)),
    focalDistance(1.0f), aperture(0.01f) {};

Ray Camera::getRay(glm::vec2 & screenSample, glm::vec2 & apertureSample) {
    
    // Setup camera variables
    glm::vec3 w = glm::normalize(target - position);
    glm::vec3 u = glm::normalize(glm::cross(w, up));
    glm::vec3 v = glm::cross(w, u);
    
    // Cached uniform variables
    float b = -tan(fovy / 2);
    float a = b * aspect;
    
    // Calculate start
    glm::vec3 start = position;
    start += u * apertureSample.x + v * apertureSample.y;
    
    // Calculate direction
    glm::vec3 dir = glm::normalize(position - start +
        focalDistance * glm::normalize(a * screenSample.x * u + b * screenSample.y * v + w));
    
    // Return the ray
    return Ray(start, target);
}
