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
        return 0;
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

