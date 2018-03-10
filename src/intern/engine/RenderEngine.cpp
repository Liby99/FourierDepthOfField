#include "engine/RenderEngine.h"

using namespace recartyar;

RenderEngine::RenderEngine() : mDepth(5) {};

int RenderEngine::depth() {
    return mDepth;
}

void RenderEngine::setDepth(int d) {
    mDepth = d;
}

void RenderEngine::render(Scene & scn, Image & img) {
    std::vector<RaySample> samples;
    generateSamples(scn, img, samples);
    renderWithSample(scn, img, samples);
    postProcessing(scn, img, samples);
}

void RenderEngine::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    // Do nothing
}

void RenderEngine::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    Camera & cam = scn.getCamera();
    #pragma omp parallel for
    for (int i = 0; i < samples.size(); i++) {
        Ray ray = cam.getRay(samples[i].imageSample, samples[i].apertureSample);
        img.addColor(samples[i].i, samples[i].j, getColor(scn, ray));
    }
}

void RenderEngine::postProcessing(Scene &scn, Image &img, std::vector<RaySample> &samples) {
    // Do nothing
}

Color RenderEngine::getColor(Scene & scn, Ray & ray) {
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

Color RenderEngine::getColor(Scene & scn, Intersection & itsct) {
    return Color::BLACK;
}
