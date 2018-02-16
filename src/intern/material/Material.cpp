#include "material/Material.h"

using namespace recartyar;

Material::Material() {}

Color Material::computeReflection(Intersection & itsct, Ray & out) {
    return Color();
}

std::pair<Ray, Color> Material::generateSample(Intersection & itsct, vec2 sample) {
    return std::make_pair(Ray(), Color::BLACK);
}

Color Material::emission() {
    return Color();
}
