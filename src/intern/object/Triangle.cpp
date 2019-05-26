#include "object/Triangle.h"

using namespace fdof;

vec3 Triangle::getBaryCentric(vec3 position) {
    vec3 result = vec3(0, 0, 0);
    vec3 p0 = v0->getPosition();
    vec3 p1 = v1->getPosition();
    vec3 p2 = v2->getPosition();
    vec3 t0 = p1 - p0, t1 = p2 - p0, t2 = position - p0;
    float d00 = dot(t0, t0);
    float d01 = dot(t0, t1);
    float d11 = dot(t1, t1);
    float d20 = dot(t2, t0);
    float d21 = dot(t2, t1);
    float denom = d00 * d11 - d01 * d01;
    result.x = (d11 * d20 - d01 * d21) / denom;
    result.y = (d00 * d21 - d01 * d20) / denom;
    result.z = 1.0f - result.x - result.y;
    return result;
}

bool Triangle::updateIntersect(Ray & ray, Intersection & intersection) {

    // Pre cache the positions
    vec3 p0 = v0->getPosition();
    vec3 p1 = v1->getPosition();
    vec3 p2 = v2->getPosition();
    vec3 n0 = v0->getNormal();
    vec3 n1 = v1->getNormal();
    vec3 n2 = v2->getNormal();

    // Same the variables
    vec3 normal = glm::cross(p1 - p0, p2 - p0);

    // If three points are in a straight line, then intersection not exist
    if (normal.x == 0 && normal.y == 0 && normal.z == 0) {
        return false;
    }
    normal = normalize(normal);

    // Calculate t
    float t = (glm::dot(p0, normal) - glm::dot(ray.origin, normal)) / glm::dot(ray.direction, normal);

    // Pre cache the position of the intersection
    vec3 position = ray.getPoint(t);
    vec3 lambda = getBaryCentric(position);

    // Check if t is greater then 0 and the position is inside the triangle and need update
    if (t > 0 &&
        lambda.x >= 0 && lambda.x <= 1 &&
        lambda.y >= 0 && lambda.y <= 1 &&
        lambda.z >= 0 && lambda.z <= 1) {

        if (n0 != vec3() || n1 != vec3() || n2 != vec3()) {
            normal = lambda.x * n0 + lambda.y * n1 + lambda.z * n2;
            normal = glm::normalize(-normal);
        }

        return intersection.update(t, position, normal);
    }

    // Not intersected
    return false;
}

void Triangle::getBoundingVertices(std::vector<vec3> & verts) {
    verts.push_back(v0->getPosition());
    verts.push_back(v1->getPosition());
    verts.push_back(v2->getPosition());
}

Triangle::Triangle(Vertex * v0, Vertex * v1, Vertex * v2) : Object() {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
    vec3 ab = v1->getPosition() - v0->getPosition();
    vec3 ac = v2->getPosition() - v0->getPosition();
    float theta = std::acos(glm::dot(glm::normalize(ab), glm::normalize(ac)));
}

Vertex & Triangle::getVertex(int i) {
    switch (i) {
        case 0: return *v0;
        case 1: return *v1;
        case 2: return *v2;
        default: throw std::invalid_argument("received negative value");
    }
}

Vertex & Triangle::getV0() {
    return *v0;
}

Vertex & Triangle::getV1() {
    return *v1;
}

Vertex & Triangle::getV2() {
    return *v2;
}

vec3 Triangle::getCenter() {
    return (v0->getPosition() + v1->getPosition() + v2->getPosition()) / 3.0f;
}
