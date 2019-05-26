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
    while (hasNextSample(scn, img)) {
        RaySample sp = getNextSample(scn, img);
        Ray ray = cam.getRay(sp.imageSample, sp.apertureSample);
        img.addColor(sp.i, sp.j, getColor(scn, ray));
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

bool RenderEngine::hasNextSample(Scene & scn, Image & img) {
    return false;
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
