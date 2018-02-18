#include "material/Lambert.h"

using namespace recartyar;

Lambert::Lambert() : Lambert(Color::WHITE) {}

Lambert::Lambert(Color color) : color(color), Material() {}

Color Lambert::brdf(Intersection & itsct, Ray & out) {
    float cosTheta = fmax(glm::dot(out.direction, itsct.normal), 0.0f);
    return color * cosTheta;
}

std::pair<Ray, Color> Lambert::reflect(Intersection & itsct) {
    vec2 sp = Sampler::random2D();
    float u = 2 * M_PI * sp.x, v = sqrt(1 - sp.y);
    vec3 magic = vec3(0.2f, 0.7f, 0.1f),
         norm = itsct.normal,
         udir = normalize(cross(norm, norm + magic)),
         vdir = normalize(cross(norm, udir));
    Ray out = Ray(itsct.position, udir * v * cos(u) + norm * sqrt(sp.y) + vdir * v * sin(u));
    return std::make_pair(out, brdf(itsct, out));
}

Color Lambert::emission() {
    return Color::BLACK;
}
