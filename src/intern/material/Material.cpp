#include "material/Material.h"

using namespace fdof;

Material::Material() {}

Color Material::brdf(Intersection & itsct, Ray & out) {
    return Color();
}

std::pair<Ray, Color> Material::reflect(Intersection & itsct) {
    return std::make_pair(Ray(), Color::BLACK);
}

Color Material::emission() {
    return Color();
}
