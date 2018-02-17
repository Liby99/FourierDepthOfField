#include <iostream>
#include "engine/PathTracer.h"

using namespace recartyar;

PathTracer::PathTracer() : Engine() {}

void PathTracer::render(Scene & scn, Image & img) {
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    Camera & cam = scn.getCamera();
    cam.aspect = float(width) / float(height);
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float x = float(i - hw + 0.5) / float(hw), y = float(j - hh + 0.5) / float(hh);
            Ray ray = cam.getRay(vec2(x, y));
            img.setColor(i, j, getColor(scn, ray));
        }
    }
}

Color PathTracer::getColor(Scene & scn, Ray & ray) {
    Intersection itsct(ray);
    if (scn.intersect(ray, itsct)) {
        return getColor(scn, itsct);
    }
    else {
        return scn.getBackground();
    }
}

Color PathTracer::getColor(Scene & scn, Intersection & itsct) {
    return Color::WHITE;
}
