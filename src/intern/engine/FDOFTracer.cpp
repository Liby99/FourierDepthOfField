#include "engine/FDOFTracer.h"

using namespace recartyar;

FDOFTracer::FDOFTracer() : FDOFTracer(1.0f) {}

FDOFTracer::FDOFTracer(float k) : PathTracer(), k(k), energy(10000), importance(4) {}

void FDOFTracer::generateSamples(Scene &scn, Image &img, std::vector<RaySample> &samples) {

    std::cout << "Generating Samples... " << std::endl;

    // First Generate Primary Samples
    std::vector<RaySample> primSmpls;
    generatePrimaryRays(scn, img, primSmpls);

    // Trace Intersections
    std::vector<Intersection> itscts;
    traceIntersections(scn, primSmpls, itscts);

    // Get circle of confusion
    traceCircleOfConfusion(scn, img, itscts, cocs);

    // Propagate lens density and spatial density
    Image lensDensity(img.width, img.height);
    Image spatialDensity(img.width, img.height);
    propagateSpectra(scn, img, itscts, cocs, spatialDensity, lensDensity);

    // Trace sampling points
    int width = img.width, height = img.height, hw = width / 2, hh = height / 2;
    SpatialDensitySampler sds(spatialDensity);
    for (auto pt : sds.getSamplingPoints()) {
        int ns = (int) lensDensity.getColor((int) pt.x, (int) pt.y).r;
        for (int i = 0; i < ns; i++) {
            vec2 sp = Sampler::random2D(), aptsp = Sampler::randomCircle();
            vec2 imgsp = vec2(float(pt.x - hw + sp.x) / hw, float(pt.y - hh + sp.y) / hh);
            samples.push_back(RaySample(pt.x, pt.y, imgsp, aptsp));
        }
    }
}

void FDOFTracer::postProcessing(Scene & scn, Image & img, std::vector<RaySample> & samples) {

    std::cout << "Reconstructing... " << std::endl;

    // First populate the samples
    int width = img.width, height = img.height;
    std::vector<std::pair<vec2, Color>> imgSamples;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int index = j * width + i;
            if (img.addCounts[index] != 0) {
                imgSamples.push_back(std::make_pair(vec2(i, j), img.getColor(i, j)));
            }
        }
    }
    
    // Then loop through all the pixels to reconstruct
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int index = j * width + i;
            if (img.addCounts[index] == 0) {
                vec2 pos(i, j);
                std::sort(imgSamples.begin(), imgSamples.end(), [pos] (std::pair<vec2, Color> p1, std::pair<vec2, Color> p2) {
                    float d1 = glm::length(p1.first - pos),
                          d2 = glm::length(p2.first - pos);
                    return d1 > d2;
                });
                Color c;
                for (int k = 0; k < 10; k++) {
                    float d = glm::length(imgSamples[k].first - pos);
                    c += imgSamples[k].second * gaussianWeight(d, cocs[index]);
                }
                img.setColor(i, j, c);
            }
        }
    }
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

        // Calculate the occlusion
        vec3 p = i1.position, q = i2.position;
        float dp = glm::dot(p - c, f), dq = glm::dot(q - c, f);
        float ap = (dp - dq) / dp * cam.aperture();
        vec3 pp = c + (p - c) * dq / dp;
        return glm::length(q - pp) < ap;
    }
    else if (i1.hit) {

        // If current is hit but the neighbor is not hit then occluded
        return true;
    }
    else {

        // If both are not hit then not occluded
        return false;
    }
}

void FDOFTracer::propagateSpectra(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs, Image & spatialDensity, Image & lensDensity) {

    // Cache the camera
    Camera & cam = scn.getCamera();
    float h = glm::tan(cam.fovy() / 2) * cam.focalDistance() * 2;
    float ox = h / img.height;
    float fhfvowh = cam.fovy() * cam.fovy() * cam.aspect() / (img.width * img.height);

    std::vector<float> occluderBuffer[img.width * img.height];

    // Build up occluder list
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {

            int currIndex = j * img.width + i;
            int coc = cocs[currIndex];
            Intersection & itsct = itscts[currIndex];

            // First check if a discontinuity occurs in this pixel
            bool flag = false;
            for (int l = j - 1; l <= j + 1; l++) {
                for (int k = i - 1; k <= i + 1; k++) {
                    if (k >= 0 && k < img.width && l >= 0 && l < img.height && !(l == j && k == i)) {

                        // Get the neighbor intersection
                        int nbIndex = l * img.width + k;
                        Intersection & nbItsct = itscts[nbIndex];

                        // Check if there's occlusion. If is then go out.
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

            // Then make the discontinuity influence a circle region given by radius of circle of confusion
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

    // Finally propagate the spectrum at each image point
    for (int j = 0; j < img.height; j++) {
        for (int i = 0; i < img.width; i++) {

            // Cache the data
            int currIndex = j * img.width + i;
            Intersection & itsct = itscts[currIndex];
            std::vector<float> & occluders = occluderBuffer[currIndex];

            // Initialize a spectrum
            Spectrum spctm(100);

            // Sort the occluders
            std::sort(occluders.begin(), occluders.end(), std::less<>());

            // Propagate the spectrum
            float prev = 0;
            for (int o = 0; o < occluders.size(); o++) {
                spctm.transport(prev - occluders[o]);
                spctm.occlude(3);
                prev = occluders[o];
            }

            // Initiate lens and spatial density to 1
            int ns = 1, ps = 1;
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
                ps = importance * mb * mb;
            }

            // Set the color to spatial density and lens density
            spatialDensity.setColor(i, j, rgb(ps * energy));
            lensDensity.setColor(i, j, rgb(ns));
        }
    }
}

float FDOFTracer::gaussianWeight(float d, float variance) {
    return std::exp(-d * d / (2 * variance)) / std::sqrt(2 * pi * variance);
}
