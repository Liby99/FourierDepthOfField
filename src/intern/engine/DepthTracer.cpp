#include "engine/DepthTracer.h"

using namespace fdof;

DepthTracer::DepthTracer() : RenderEngine(), mNear(0.1f), mFar(100.0f) {}

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

void DepthTracer::initiateGenerator(Scene &scn, Image &img) {
    currI = 0;
    currJ = 0;
    hw = img.width / 2;
    hh = img.height / 2;
}

RaySample DepthTracer::getNextSample(Scene & scn, Image & img) {
    if (currI < img.width - 1) {
        currI++;
    }
    else {
        currI = 0;
        currJ++;
    }
    vec2 imgsp = vec2((currI - hw + 0.5f) / hw, (currJ - hh + 0.5f) / hh);
    return { currI, currJ, imgsp };
}

bool DepthTracer::hasNextSample(Scene & scn, Image & img) const {
    return currJ < img.height - 1 || currI < img.width - 1;
}

Color DepthTracer::getColor(Scene & scn, Ray & ray) const {
    Intersection itsct(ray);
    if (scn.intersect(ray, itsct)) {
        return Color(fmin(fmax((itsct.distToOrigin() - mNear) / (mFar - mNear), 0.0), 1.0));
    }
    else {
        return Color::WHITE;
    }
}
