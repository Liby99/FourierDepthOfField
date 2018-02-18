#include "engine/PathTracer.h"

using namespace recartyar;

PathTracer::PathTracer() : Engine(), mSpp(4), mDepth(5) {}

int PathTracer::superSampling() {
    return mSpp;
}

void PathTracer::setSuperSampling(int spp) {
    mSpp = spp;
}

int PathTracer::depth() {
    return mDepth;
}

void PathTracer::setDepth(int d) {
    mDepth = d;
}

void PathTracer::render(Scene & scn, Image & img) {
    std::vector<RaySample> samples;
    generateSamples(scn, img, samples);
    renderWithSample(scn, img, samples);
}

void PathTracer::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    Camera & cam = scn.getCamera();
    cam.setAspect(float(width) / float(height));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < mSpp; k++) {
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

Color PathTracer::getColor(Scene & scn, Intersection & itsct) {
    Object & obj = itsct.getObject();
    if (obj.hasMaterial()) {
        Material & mat = obj.getMaterial();
        
        // First calculate emission
        Color e = mat.emission(), b = Color::BLACK, l = Color::BLACK;
        
        // Then calculate scene reflection
        std::pair<Ray, Color> p = mat.reflect(itsct);
        if (p.second != Color::BLACK) {
            p.first.increment();
            p.first.depth = itsct.getRay().depth + 1;
            b =  p.second * getColor(scn, p.first);
        }
        
        // Finally compute light reflection
        if (scn.hasLight()) {
            Light & lgt = getRandomLight(scn);
            Ray ref(itsct.position, lgt.getToLightDir(itsct));
            ref.increment();
            Intersection sditsct(ref);
            if (!scn.intersect(ref, sditsct)) {
                l = mat.brdf(itsct, ref) * lgt.getColor(itsct, sditsct);
            }
        }
        
        return e + b + l;
    }
    else {
        return Color::BLACK;
    }
}

Light & PathTracer::getRandomLight(Scene & scn) {
    return scn.getLight(int(Sampler::random() * scn.lightCount()));
}
