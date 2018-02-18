#include "material/Lambert.h"

using namespace recartyar;

Lambert::Lambert() : Lambert(Color::WHITE) {}

Lambert::Lambert(Color color) : color(color), Material() {}

Color Lambert::brdf(Intersection & itsct, Ray & out) {
    return color;
}

std::pair<Ray, Color> Lambert::reflect(Intersection & itsct) {
    vec2 sp = Sampler::random2D();
    float u = 2 * M_PI * sp.x;
    float v = sqrt(1 - sp.y);
    vec3 norm = itsct.normal;
    vec3 udir = normalize(cross(norm, norm + vec3(0.2f, 0.7f, 0.1f)));
    vec3 vdir = normalize(cross(norm, udir));
    vec3 dir = udir * v * cos(u) + norm * sqrt(sp.y) + vdir * v * sin(u);
    Ray ray = Ray(itsct.position, dir);
    return std::make_pair(ray, color);
}

Color Lambert::emission() {
    return Color::BLACK;
}
