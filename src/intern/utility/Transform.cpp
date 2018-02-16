#include "utility/Transform.h"

using namespace recartyar;

Transform::Transform() : position(vec3(0, 0, 0)), rotation(vec3(0, 0, 0)), scale(vec3(1, 1, 1)) {}

mat4 Transform::getTranslateMatrix() {
    return glm::translate(mat4(1.0f), position);
}

mat4 Transform::getRotateXMatrix() {
    return glm::rotate(mat4(1.0f), rotation.x, vec3(1, 0, 0));
}

mat4 Transform::getRotateYMatrix() {
    return glm::rotate(mat4(1.0f), rotation.y, vec3(0, 1, 0));
}

mat4 Transform::getRotateZMatrix() {
    return glm::rotate(mat4(1.0f), rotation.z, vec3(0, 0, 1));
}

mat4 Transform::getRotateMatrix() {
    return getRotateZMatrix() * getRotateYMatrix() * getRotateXMatrix();
}

mat4 Transform::getScaleMatrix() {
    return glm::scale(mat4(1.0f), scale);
}

mat4 Transform::getTransform() {
    return getTranslateMatrix() * getRotateMatrix() * getScaleMatrix();
}
