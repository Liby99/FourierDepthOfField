#include "engine/PathTracer.h"

using namespace recartyar;

PathTracer::PathTracer() : Engine(), spp(4) {}

void PathTracer::setSuperSampling(int spp) {
    this->spp = spp;
}

int PathTracer::getSuperSampling() {
    return spp;
}

void PathTracer::render(Scene & scn, Image & img) {
    std::vector<RaySample> samples;
    generateSamples(scn, img, samples);
    renderWithSample(scn, img, samples);
}

void PathTracer::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    Camera & cam = scn.getCamera();
    cam.aspect = float(width) / float(height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < spp; k++) {
                vec2 sp = Sampler::random2D(), aptsp = Sampler::randomCircle(),
                    imgsp = vec2(float(i - hw + sp.x) / hw, float(j - hh + sp.y) / hh);
                samples.push_back(RaySample(i, j, imgsp, aptsp));
            }
        }
    }
}

void PathTracer::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    Camera & cam = scn.getCamera();
    #pragma omp parallel for
    for (int i = 0; i < samples.size(); i++) {
        Ray ray = cam.getRay(samples[i].imageSample, samples[i].apertureSample);
        img.addColor(samples[i].i, samples[i].j, getColor(scn, ray));
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
    
    return Color(1, 1, 1);
    
    Object & obj = itsct.getObject();
    if (obj.hasMaterial()) {
        Material & mat = obj.getMaterial();
        
        // First calculate emission
        Color c = mat.emission();
        
        // Then calculate scene reflection
        std::pair<Ray, Color> p = mat.reflect(itsct);
        if (p.second != Color::BLACK) {
            c += p.second * getColor(scn, p.first);
        }
        
        // Finally compute light reflection
        if (scn.hasLight()) {
            Light & lgt = getRandomLight(scn);
            
        }
        
        return c;
    }
    else {
        return Color::BLACK;
    }
}

Light & PathTracer::getRandomLight(Scene & scn) {
    return scn.getLight(int(Sampler::random() * scn.lightCount()));
}
