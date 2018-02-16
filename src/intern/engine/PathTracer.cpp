#include "engine/PathTracer.h"

using namespace recartyar;

PathTracer::PathTracer() : Engine() {}

void PathTracer::render(Scene & scn, Image & img) {
    int width = img.width, height = img.height;
    Camera & cam = scn.getCamera();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float x = float(i) / float(width) + 0.5f, y = float(j) / float(height) + 0.5f;
            Ray ray = cam.getRay(vec2(x, y), vec2(0, 0));
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
