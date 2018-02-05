#include "object/Sphere.h"

bool Sphere::updateIntersect(Ray & ray, Intersection & intersection, float frame) {
    
    vec3 p0 = ray.getOrigin();
    vec3 p1 = ray.getDirection();
    
    float t;
    bool hit = false;
    float a = dot(p1, p1);
    float b = 2.0f * dot(p1, p0);
    float c = dot(p0, p0) - radius * radius;
    float t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    float t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

    if (t1 > 0 && t2 > 0) {
        t = min(t1, t2);
    }
    else if (t1 * t2 < 0) {
        t = max(t1, t2);
    }
    else {
        return false;
    }
        
    // Update the intersection
    vec3 position = ray.getPoint(t);
    
    // Return intersection update
    return intersection.update(t, position, position);
}

vector<vec3> Sphere::getBoundingVertices() {
    vector<vec3> result;
    result.push_back(vec3(radius, radius, radius));
    result.push_back(vec3(radius, radius, -radius));
    result.push_back(vec3(radius, -radius, radius));
    result.push_back(vec3(radius, -radius, -radius));
    result.push_back(vec3(-radius, radius, radius));
    result.push_back(vec3(-radius, radius, -radius));
    result.push_back(vec3(-radius, -radius, radius));
    result.push_back(vec3(-radius, -radius, -radius));
    return result;
}

vec3 Sphere::sampleSurfacePointHelper(float t) {
    vec2 sample = Sampler::random2D();
    float theta = 2 * pi * sample.x;
    float phi = pi * sample.y;
    return radius * vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}

Sphere::Sphere() {
    setRadius(1);
    surfaceArea = 4 * pi;
}

Sphere::Sphere(float radius) {
    setRadius(radius);
    surfaceArea = 4 * pi * radius * radius;
}

float Sphere::getRadius() {
    return radius;
}

void Sphere::setRadius(float radius) {
    this->radius = radius;
}
