#include "material/Material.h"

using namespace recartyar;

Material::Material() {}

Color Material::getReflection(Intersection & itsct, Ray & out) {
    return Color();
}

std::pair<Ray, Color> Material::reflect(Intersection & itsct) {
    return std::make_pair(Ray(), Color::BLACK);
}

Color Material::emission() {
    return Color();
}
