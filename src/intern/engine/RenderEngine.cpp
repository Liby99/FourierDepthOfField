#include "engine/RenderEngine.h"

using namespace fdof;

RenderEngine::RenderEngine() : mDepth(5) {};

int RenderEngine::depth() {
    return mDepth;
}

void RenderEngine::setDepth(int d) {
    mDepth = d;
}

void RenderEngine::render(Scene & scn, Image & img) {
    preProcessing(scn, img);
    renderWithSample(scn, img);
    postProcessing(scn, img);
}

void RenderEngine::preProcessing(Scene & scn, Image & img) {
    scn.getCamera().setAspect(float(img.width) / float(img.height));
}

void RenderEngine::renderWithSample(Scene & scn, Image & img) {
    initiateGenerator(scn, img);
    Camera & cam = scn.getCamera();
    std::vector<RaySample> samples(CHUNK_SIZE);
    int amount = 0;
    while (true) {

        // First get the samples;
        amount = 0;
        while (hasNextSample(scn, img) && amount < CHUNK_SIZE) {
            samples[amount++] = getNextSample(scn, img);
        }

        // Break if amount is 0
        if (!amount) break;

        // Then parallel through the chunk
        #pragma omp parallel for
        for (int i = 0; i < amount; i++) {
            Ray ray = cam.getRay(samples[i].imageSample, samples[i].apertureSample);
            samples[i].color = getColor(scn, ray);
        }

        // Finally accumulate the colors
        for (int i = 0; i < amount; i++) {
            img.addColor(samples[i].i, samples[i].j, samples[i].color);
        }
    }
}

void RenderEngine::postProcessing(Scene &scn, Image &img) {
    // Do nothing
}

void RenderEngine::initiateGenerator(Scene & scn, Image & img) {
    // Do nothing
}

RaySample RenderEngine::getNextSample(Scene & scn, Image & img) {
    return { 0, 0, vec2(0, 0) };
}

bool RenderEngine::hasNextSample(Scene & scn, Image & img) const {
    return false;
}

Color RenderEngine::getColor(Scene & scn, Ray & ray) const {
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

Color RenderEngine::getColor(Scene & scn, Intersection & itsct) const {
    return Color::BLACK;
}
