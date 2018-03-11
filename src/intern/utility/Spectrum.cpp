#include "utility/Spectrum.h"

using namespace recartyar;

Spectrum::Spectrum(int num) {
    for (int i = 0; i < num; i++) {
        samples.push_back(vec2(
            Sampler::random() * 40 - 20,
            Sampler::random() * pi - pi / 2
        ));
    }
}

void Spectrum::transport(float dist) {
    for (int i = 0; i < samples.size(); i++) {
        samples[i].y += samples[i].x * dist;
    }
}

void Spectrum::occlude(float ox) {
    for (int i = 0; i < samples.size(); i++) {
        samples[i].x += ox * (glm::floor(glm::mod(Sampler::random(), 1.0f) * 3) - 2);
    }
}

void Spectrum::saveImage(const std::string & name) {
    Image img(40, 40);
    for (int i = 0; i < samples.size(); i++) {
        img.setColor(samples[i].x + 20, samples[i].y + 20, rgb::WHITE);
    }
    img.save(name.c_str());
}
