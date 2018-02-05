#include "material/Material.h"

Material::Material() {}

Color Material::computeReflection(Intersection & i, Ray & out) {
    return Color();
}

pair<Ray, Color> Material::generateSample(Intersection & intersection, vec2 sample) {
    return make_pair(Ray(), Color::BLACK);
}

vector<pair<Ray, Color>> Material::reflection(Intersection & intersection, int amount) {
    vector<pair<Ray, Color>> result;
    vector<vec2> samples = Sampler::jitter2D(amount);
    for (int i = 0; i < samples.size(); i++) {
        pair<Ray, Color> s = generateSample(intersection, samples[i]);
        if (s.second != Color::BLACK) {
            result.push_back(s);
        }
    }
    return result;
}

Color Material::emission() {
    return Color();
}
