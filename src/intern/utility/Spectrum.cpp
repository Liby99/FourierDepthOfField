#include "utility/Spectrum.h"

using namespace recartyar;

Spectrum::Spectrum(int num) {
    for (int i = 0; i < num; i++) {
        samples.push_back(vec2(
            Sampler::random() * 5 - 2.5f,
            Sampler::random() * pi - pi / 2
        ));
    }
}

void Spectrum::transport(float dist) {
    for (int i = 0; i < samples.size(); i++) {
        samples[i].y += samples[i].x * dist;
    }
}

void Spectrum::occlude(Spectrum & other) {
    for (int i = 0; i < std::min(samples.size(), other.samples.size()); i++) {
        samples[i] += other.samples[i];
    }
}
