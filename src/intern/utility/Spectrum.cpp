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
        samples[i].x += 1 / ox * (glm::floor(glm::mod(Sampler::random(), 1.0f) * 3.0f) - 1.0f);
    }
}

void Spectrum::saveImage(const std::string & name) {
    Image img(40, 40);
    for (int i = 0; i < samples.size(); i++) {
        int x = samples[i].x + 20, y = samples[i].y + 20;
        if (x >= 0 && x < img.width && y >= 0 && y < img.height) {
            img.setColor(x, y, rgb::WHITE);
        }
    }
    img.save(name.c_str());
}
