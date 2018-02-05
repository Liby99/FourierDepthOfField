#include "material/Lambert.h"

Lambert::Lambert() : Lambert(Color::WHITE) {}

Lambert::Lambert(Color color) : Material() {
    setColor(color);
}

void Lambert::setColor(Color color) {
    this->color = color;
}

Color Lambert::getColor() {
    return color;
}

Color Lambert::computeReflection(Intersection & i, Ray & out) {
    return color;
}

pair<Ray, Color> Lambert::generateSample(Intersection & intersection, vec2 sample) {
    float u = 2 * pi * sample.x;
    float v = sqrt(1 - sample.y);
    vec3 norm = intersection.getNormal();
    vec3 udir = normalize(cross(norm, norm + vec3(0.2f, 0.7f, 0.1f)));
    vec3 vdir = normalize(cross(norm, udir));
    vec3 dir = udir * v * cos(u) + norm * sqrt(sample.y) + vdir * v * sin(u);
    Ray ray = Ray(intersection.getPosition(), dir, intersection.getRay().getDepth() + 1);
    return make_pair(ray, color);
}

Color Lambert::emission() {
    return Color::BLACK;
}
