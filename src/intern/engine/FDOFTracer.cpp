#include "engine/FDOFTracer.h"

using namespace recartyar;

FDOFTracer::FDOFTracer() : PathTracer() {}

void FDOFTracer::generateSamples(Scene &scn, Image &img, std::vector<RaySample> &samples) {

    std::vector<RaySample> primSmpls;
    generatePrimaryRays(scn, img, primSmpls);

    std::vector<Intersection> itscts;
    traceIntersections(scn, primSmpls, itscts);

    std::vector<int> cocs;
    traceCircleOfConfusion(scn, img, itscts, cocs);

    // Generate Circle Of Confusion Image (Bounded by 50)
//    Image cocImg(img.width, img.height);
//    for (int i = 0; i < img.width; i++) {
//        for (int j = 0; j < img.height; j++) {
//            cocImg.setColor(i, j, rgb(cocs[j * img.width + i] / 50.0f));
//        }
//    }
//    cocImg.save("cubes_coc_new.bmp");

    std::vector<Spectrum> spectra;
    propagateSpectra(scn, img, itscts, cocs, spectra);
}

void FDOFTracer::generatePrimaryRays(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    Camera & cam = scn.getCamera();
    cam.setAspect(float(width) / float(height));
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            vec2 imgsp = vec2(float(i - hw + 0.5) / hw, float(j - hh + 0.5) / hh);
            samples.push_back(RaySample(i, j, imgsp));
        }
    }
}

void FDOFTracer::traceIntersections(Scene & scn, std::vector<RaySample> & samples, std::vector<Intersection> & itscts) {
    for (int i = 0; i < samples.size(); i++) {
        Ray ray = scn.getCamera().getRay(samples[i].imageSample);
        Intersection itsct(ray);
        scn.intersect(ray, itsct);
        itscts.push_back(itsct);
    }
}

float FDOFTracer::getCircleOfConfusion(Camera & cam, Intersection & itsct) {
    if (itsct.hit) {
        vec3 f = glm::normalize(cam.target() - cam.position());
        float dp = glm::length(glm::dot(itsct.position - cam.position(), f) * f);
        return glm::abs(cam.focalDistance() - dp) / dp * cam.aperture();
    }
    else {
        return cam.aperture();
    }
}

void FDOFTracer::traceCircleOfConfusion(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs) {
    Camera & cam = scn.getCamera();
    float h = glm::tan(cam.fovy() / 2) * cam.focalDistance() * 2;
    float ratio = img.height / h;
    for (auto &itsct : itscts) {
        cocs.push_back((int) glm::ceil(getCircleOfConfusion(cam, itsct) * ratio));
    }
}

bool FDOFTracer::checkOcclusion(Camera & cam, Intersection & i1, Intersection & i2) {
    vec3 c = cam.position(), f = glm::normalize(cam.target() - cam.position());

    // Check the hit status
    if (i1.hit && i2.hit) {

        // If neighbor is further than current then the current is not occluded
        if (i2.t > i1.t) {
            return false;
        }

        // Calculate the occlusion
        vec3 p = i1.position, q = i2.position;
        float dp = glm::dot(p - c, f), dq = glm::dot(q - c, f);
        float ap = (dp - dq) / dp * cam.aperture();
        vec3 pp = c + (p - c) * dq / dp;
        return glm::length(q - pp) < ap;
    }
    else if (i1.hit) {

        // If current is hit but the neighbor is not hit then not occluded
        return false;
    }
    else if (i2.hit) {
        return true;
    }
    else {

        // If both are not hit then not occluded
        return false;
    }
}

bool occluderCmp(const vec2 & o1, const vec2 & o2) {
    return o1.x > o2.x;
}

void FDOFTracer::propagateSpectra(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs, std::vector<Spectrum> & spectra) {

    float k = 1.0f;

    // Cache the camera
    Camera & cam = scn.getCamera();
    float h = glm::tan(cam.fovy() / 2) * cam.focalDistance() * 2;
    float ox = h / img.height;

    std::vector<float> * occluderBuffer = new std::vector<float>[img.width * img.height];

    // Loop through all the pixels
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {

            int currIndex = j * img.width + i;
            Intersection & itsct = itscts[currIndex];

            for (int l = j - 1; l <= j + 1; l++) {
                for (int k = i - 1; k <= i + 1; k++) {
                    if (k >= 0 && k < img.width && l >= 0 && l < img.height && !(l == j && k == i)) {

                        int nbIndex = k * img.width + l;
                        Intersection & nbItsct = itscts[nbIndex];

                        if (checkOcclusion(cam, itsct, nbItsct)) {
                            occluderBuffer[];
                        }
                    }
                }
            }
        }
    }
}

