#include "engine/DepthTracer.h"

using namespace recartyar;

DepthTracer::DepthTracer() : PathTracer(), mNear(0.1f), mFar(100.0f) {}

float DepthTracer::near() {
    return mNear;
}

void DepthTracer::setNear(float n) {
    mNear = n;
}

float DepthTracer::far() {
    return mFar;
}

void DepthTracer::setFar(float f) {
    mFar = f;
}

void DepthTracer::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    Camera & cam = scn.getCamera();
    cam.setAspect(float(width) / float(height));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            vec2 imgsp = vec2(float(i - hw + 0.5) / hw, float(j - hh + 0.5) / hh);
            samples.push_back(RaySample(i, j, imgsp));
        }
    }
}

Color DepthTracer::getColor(Scene & scn, Ray & ray) {
    Intersection itsct(ray);
    if (scn.intersect(ray, itsct)) {
        return Color(fmin(fmax((itsct.distToOrigin() - mNear) / (mFar - mNear), 0.0), 1.0));
    }
    else {
        return Color::WHITE;
    }
}
