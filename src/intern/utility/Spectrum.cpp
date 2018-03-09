#include "utility/Spectrum.h"

using namespace recartyar;

Spectrum::Spectrum(int num) {
    for (int i = 0; i < num; i++) {
        samples.push_back(vec2(
            Sampler::random() * 10 - 5,
            Sampler::random() * pi - pi / 2
        ));
    }
}

void Spectrum::transport(float dist) {
    
}
