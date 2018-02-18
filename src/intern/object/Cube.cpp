#include "object/Cube.h"

using namespace recartyar;

Cube::Cube() : Cube(1, 1, 1) {}

Cube::Cube(float width, float height, float length) : width(width), height(height), length(length) {}

bool Cube::updateIntersect(Ray & ray, Intersection & itsct) {
    
    float hw = width / 2, hh = height / 2, hl = length / 2;
    
    // Get the min and max corner
    vec3 minCorner = vec3(-hw, -hh, -hl);
    vec3 maxCorner = vec3(hw, hh, hl);
    
    float txmin = (minCorner.x - ray.origin.x) / ray.direction.x;
    float txmax = (maxCorner.x - ray.origin.x) / ray.direction.x;
    if (txmin > txmax) std::swap(txmin, txmax);
    
    float tymin = (minCorner.y - ray.origin.y) / ray.direction.y;
    float tymax = (maxCorner.y - ray.origin.y) / ray.direction.y;
    if (tymin > tymax) std::swap(tymin, tymax);
    
    float tzmin = (minCorner.z - ray.origin.z) / ray.direction.z;
    float tzmax = (maxCorner.z - ray.origin.z) / ray.direction.z;
    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    
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
    return itsct.update(t, position, sign * normal);
}
