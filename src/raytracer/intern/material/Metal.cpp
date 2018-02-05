#include "material/Metal.h"

Metal::Metal() : Metal(Color::WHITE) {}

Metal::Metal(Color color) : Material() {
    setColor(color);
}

Color Metal::getColor() {
    return color;
}

void Metal::setColor(Color color) {
    this->color = color;
}

Color Metal::computeReflection(Intersection & i, Ray & out) {
    return Color::BLACK;
}

pair<Ray, Color> Metal::generateSample(Intersection & intersection, vec2 sample) {
    
    // Calculate the reflection direction
    vec3 norm = intersection.getNormal();
    vec3 in = intersection.getRay().getDirection();
    vec3 dir = in - 2.0f * norm * dot(norm, in);
    
    // Calculate the reflection ray
    Ray reflect = Ray(intersection.getPosition(), dir);
    reflect.increment();
    
    return make_pair(reflect, color);
}

vector<pair<Ray, Color>> Metal::reflection(Intersection & intersection, int amount) {
    vector<pair<Ray, Color>> result;
    result.push_back(generateSample(intersection, vec2(0, 0)));
    return result;
}

Color Metal::emission() {
    return Color::BLACK;
}
