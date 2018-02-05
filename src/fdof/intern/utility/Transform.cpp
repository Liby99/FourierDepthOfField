#include "utility/Transform.h"

using namespace fdof;

Transform::Transform() : position(glm::vec3(0, 0, 0)), rotation(glm::vec3(0, 0, 0)), scale(glm::vec3(1, 1, 1)) {}

glm::mat4 Transform::getTranslateMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Transform::getRotateXMatrix() {
    return glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1, 0, 0));
}

glm::mat4 Transform::getRotateYMatrix() {
    return glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1, 0));
}

glm::mat4 Transform::getRotateZMatrix() {
    return glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1));
}

glm::mat4 Transform::getRotateMatrix() {
    return getRotateZMatrix() * getRotateYMatrix() * getRotateXMatrix();
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 Transform::getTransform() {
    return getTranslateMatrix() * getRotateMatrix() * getScaleMatrix();
}
