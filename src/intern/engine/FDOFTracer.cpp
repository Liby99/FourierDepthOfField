#include "engine/FDOFTracer.h"

using namespace recartyar;

FDOFTracer::FDOFTracer() : FDOFTracer(1.0f) {}

FDOFTracer::FDOFTracer(float k) : PathTracer(), k(k) {}

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

    std::vector<int> lensDensity;
    std::vector<float> spatialDensity;
    propagateSpectra(scn, img, itscts, cocs, lensDensity, spatialDensity);
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
//        if (i2.t > i1.t) {
//            return false;
//        }

        // Calculate the occlusion
        vec3 p = i1.position, q = i2.position;
        float dp = glm::dot(p - c, f), dq = glm::dot(q - c, f);
        float ap = (dp - dq) / dp * cam.aperture();
        vec3 pp = c + (p - c) * dq / dp;
        return glm::length(q - pp) < ap;
    }
    else if (i1.hit) {

        // If current is hit but the neighbor is not hit then not occluded
        return true;
    }
    else if (i2.hit) {


        return false;
    }
    else {

        // If both are not hit then not occluded
        return false;
    }
}

bool occluderCmp(const vec2 & o1, const vec2 & o2) {
    return o1.x > o2.x;
}

void FDOFTracer::propagateSpectra(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs, std::vector<int> & lensDensity, std::vector<float> & spatialDensity) {

    // Cache the camera
    Camera & cam = scn.getCamera();
    float h = glm::tan(cam.fovy() / 2) * cam.focalDistance() * 2;
    float ox = h / img.height;
    float fhfvowh = cam.fovy() * cam.fovy() * cam.aspect() / (img.width * img.height);

    std::vector<float> occluderBuffer[img.width * img.height];

    // Loop through all the pixels
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {

            int currIndex = j * img.width + i;
            int coc = cocs[currIndex];
            Intersection & itsct = itscts[currIndex];

            bool flag = false;
            for (int l = j - 1; l <= j + 1; l++) {
                for (int k = i - 1; k <= i + 1; k++) {
                    if (k >= 0 && k < img.width && l >= 0 && l < img.height && !(l == j && k == i)) {

                        int nbIndex = l * img.width + k;
                        Intersection & nbItsct = itscts[nbIndex];

                        if (checkOcclusion(cam, itsct, nbItsct)) {
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag) {
                    break;
                }
            }

            if (flag) {
                for (int l = j - coc; l < j + coc; l++) {
                    for (int k = i - coc; k < i + coc; k++) {
                        float d = glm::length(vec2(i, j) - vec2(k, l));
                        if (k >= 0 && k < img.width && l >= 0 && l < img.height && !(i == k && j == l) && d < coc) {
                            int ocIndex = l * img.width + k;
                            occluderBuffer[ocIndex].push_back(itsct.t);
                        }
                    }
                }
            }
        }
    }

    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {
            int currIndex = j * img.width + i;
            Intersection & itsct = itscts[currIndex];
            std::vector<float> & occluders = occluderBuffer[currIndex];

            Spectrum spctm(100);

            std::sort(occluders.begin(), occluders.end(), std::less<>());

            float prev = 0;
            for (int o = 0; o < occluders.size(); o++) {
                spctm.transport(prev - occluders[o]);
                spctm.occlude(3);
                prev = occluders[o];
            }

            int ns, ps;

            if (itsct.hit || occluders.size() > 0) {

                // If hit, transport to hit position
                if (itsct.hit) {
                    spctm.transport(prev - itsct.t);
                }

                // Get variance
                float variance = spctm.getVariance(cam.focalDistance());
                ns = (int) glm::ceil(this->k * std::pow(variance, 0.66667f));

                // Get Maximum Band Width
                spctm.filterAperture(cam.aperture(), cam.focalDistance());
                float mb = spctm.getMaximumBandwidth();
                ps = mb * mb;
            }
            else {

                ns = 0;
                ps = 0;
            }

            lensDensity.push_back(ns);
            spatialDensity.push_back(ps);
        }
    }
}

