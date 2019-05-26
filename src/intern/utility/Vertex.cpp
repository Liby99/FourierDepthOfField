#include "utility/Vertex.h"

using namespace fdof;

Vertex::Vertex() {
    setPosition(vec3());
    setNormal(vec3());
}

Vertex::Vertex(vec3 position) {
    setPosition(position);
    setNormal(vec3());
}

Vertex::Vertex(vec3 position, vec3 normal) {
    setPosition(position);
    setNormal(normal);
}

vec3 Vertex::getPosition() {
    return position;
}

void Vertex::setPosition(vec3 position) {
    this->position = position;
}

void Vertex::setPositionX(float x) {
    position.x = x;
}

void Vertex::setPositionY(float y) {
    position.y = y;
}

void Vertex::setPositionZ(float z) {
    position.z = z;
}

vec3 Vertex::getNormal() {
    return normal;
}

void Vertex::setNormal(vec3 normal) {
    this->normal = normal;
}

void Vertex::setNormalX(float x) {
    normal.x = x;
}

void Vertex::setNormalY(float y) {
    normal.y = y;
}

void Vertex::setNormalZ(float z) {
    normal.z = z;
}

void Vertex::addUnnormalized(vec3 normal) {
    this->normal += normal;
}

void Vertex::divideNormal(float num) {
    this->normal /= num;
}

void Vertex::normalize() {
    this->normal = glm::normalize(this->normal);
}
