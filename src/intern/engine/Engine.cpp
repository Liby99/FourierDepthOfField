#include "engine/Engine.h"

using namespace recartyar;

Engine::Engine() {};

int Engine::depth() {
    return mDepth;
}

void Engine::setDepth(int d) {
    mDepth = d;
}

void Engine::render(Scene & scn, Image & img) {
    std::vector<RaySample> samples;
    generateSamples(scn, img, samples);
    renderWithSample(scn, img, samples);
}

void Engine::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    // Do nothing
}

void Engine::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    Camera & cam = scn.getCamera();
    #pragma omp parallel for
    for (int i = 0; i < samples.size(); i++) {
        Ray ray = cam.getRay(samples[i].imageSample, samples[i].apertureSample);
        img.addColor(samples[i].i, samples[i].j, getColor(scn, ray));
    }
}

Color Engine::getColor(Scene & scn, Ray & ray) {
    if (ray.depth < mDepth) {
        Intersection itsct(ray);
        if (scn.intersect(ray, itsct)) {
            return getColor(scn, itsct);
        }
        else {
            return scn.getBackground();
        }
    }
    else {
        return Color::BLACK;
    }
}

Color Engine::getColor(Scene & scn, Intersection & itsct) {
    return Color::BLACK;
}
