#include "object/Cube.h"

const float Cube::DEFAULT_SIZE = 1;

bool Cube::updateIntersect(Ray & ray, Intersection & intersection, float frame) {
    
    // Get the min and max corner
    vec3 minCorner = getMinCorner();
    vec3 maxCorner = getMaxCorner();
    
    vec3 ori = ray.getOrigin();
    vec3 dir = ray.getDirection();
    
    float txmin = (minCorner.x - ori.x) / dir.x;
    float txmax = (maxCorner.x - ori.x) / dir.x;
    if (txmin > txmax) swap(txmin, txmax);
    
    float tymin = (minCorner.y - ori.y) / dir.y;
    float tymax = (maxCorner.y - ori.y) / dir.y;
    if (tymin > tymax) swap(tymin, tymax);
    
    float tzmin = (minCorner.z - ori.z) / dir.z;
    float tzmax = (maxCorner.z - ori.z) / dir.z;
    if (tzmin > tzmax) swap(tzmin, tzmax);
    
    float tmin = fmax(fmax(txmin, tymin), tzmin);
    float tmax = fmin(fmin(txmax, tymax), tzmax);
    
    if (tmax - tmin < 0) {
        return false;
    }
    
    float t;
    vec3 normal;
    float sign;
    if (tmin > 0 && tmax > 0) {
        t = tmin;
        sign = 1;
    }
    else if (tmin < 0 && tmax > 0) {
        t = tmax;
        sign = -1;
    }
    else {
        return false;
    }
    
    vec3 position = ray.getPoint(t);
        
    // Calculate the normal
    if (t == tymin || t == tymax) normal = position[1] > 0 ? vec3(0, 1, 0) : vec3(0, -1, 0);
    else if (t == tzmin || t == tzmax) normal = position[2] > 0 ? vec3(0, 0, 1) : vec3(0, 0, -1);
    else normal = position[0] > 0 ? vec3(1, 0, 0) : vec3(-1, 0, 0);
    
    // Try updating the intersection
    return intersection.update(t, position, sign * normal);
}

vector<vec3> Cube::getBoundingVertices() {
    float hw = width / 2;
    float hh = height / 2;
    float hl = length / 2;
    vector<vec3> result;
    result.push_back(vec3(hw, hh, hl));
    result.push_back(vec3(hw, hh, -hl));
    result.push_back(vec3(hw, -hh, hl));
    result.push_back(vec3(hw, -hh, -hl));
    result.push_back(vec3(-hw, hh, hl));
    result.push_back(vec3(-hw, hh, -hl));
    result.push_back(vec3(-hw, -hh, hl));
    result.push_back(vec3(-hw, -hh, -hl));
    return result;
}

vec3 Cube::sampleSurfacePointHelper(float t) {
    
    // Randomize Face
    int face = -1;
    float sd = length * height, td = width * length, fb = width * height;
    float total = sd + td + fb;
    float rd = Sampler::random() * total;
    if (rd < sd) {
        face = rand() % 2;
    }
    else if (rd < sd + td) {
        face = rand() % 2 + 2;
    }
    else {
        face = rand() % 2 + 4;
    }
    
    // Get Sample
    vec2 sample = Sampler::random2D();
    
    // Initiate Corner Vector and result point
    vec3 corner = vec3(width / 2, height / 2, length / 2), point;
    int axis = face / 2, sign = face % 2;
    int a1 = (face + 1) % 3, a2 = (face + 2) % 3;
    
    // Setup point
    point[axis] = pow(-1, sign) * corner[axis];
    point[a1] = -corner[a1] + 2 * corner[a1] * sample.x;
    point[a2] = -corner[a2] + 2 * corner[a2] * sample.y;
    
    // Return the sample
    return point;
}

Cube::Cube() : Object() {
    setWidth(DEFAULT_SIZE);
    setHeight(DEFAULT_SIZE);
    setLength(DEFAULT_SIZE);
    surfaceArea = pow(DEFAULT_SIZE, 3);
}

Cube::Cube(float width, float height, float length) {
    setWidth(width);
    setHeight(height);
    setLength(length);
    surfaceArea = width * height * length;
}

float Cube::getWidth() {
    return width;
}

void Cube::setWidth(float width) {
    this->width = width;
}

float Cube::getHeight() {
    return height;
}

void Cube::setHeight(float height) {
    this->height = height;
}

float Cube::getLength() {
    return length;
}

void Cube::setLength(float length) {
    this->length = length;
}

vec3 Cube::getMaxCorner() {
    return vec3(width / 2, height / 2, length / 2);
}

vec3 Cube::getMinCorner() {
    return -getMaxCorner();
}
