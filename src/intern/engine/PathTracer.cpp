#include "engine/PathTracer.h"

using namespace fdof;

PathTracer::PathTracer() : PathTracer(4) {}

PathTracer::PathTracer(int spp) : RenderEngine(), mSpp(spp) {}

int PathTracer::superSampling() {
    return mSpp;
}

void PathTracer::setSuperSampling(int spp) {
    mSpp = spp;
}

void PathTracer::initiateGenerator(Scene & scn, Image & img) {
    currI = 0, currJ = 0, currK = 0, hw = img.width / 2, hh = img.height / 2;
}

RaySample PathTracer::getNextSample(Scene & scn, Image & img) {
    if (currK < mSpp - 1) {
        currK++;
    }
    else {
        currK = 0;
        if (currI < img.width - 1) {
            currI++;
        }
        else {
            currI = 0;
            currJ++;
        }
    }
    vec2 sp = Sampler::random2D(), aptSp = Sampler::randomCircle();
    vec2 imgsp = vec2((currI - hw + sp.x) / hw, (currJ - hh + sp.y) / hh);
    return { currI, currJ, imgsp, aptSp };
}

bool PathTracer::hasNextSample(Scene & scn, Image & img) {
    return currK < mSpp - 1 || currJ < img.height - 1 || currI < img.width - 1;
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
            b = p.second * RenderEngine::getColor(scn, p.first);
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

        // Add up all the color
        return e + b + l;
    }
    else {

        // If no material then return black
        return Color::BLACK;
    }
}

Light & PathTracer::getRandomLight(Scene & scn) {
    return scn.getLight(int(glm::mod(Sampler::random(), 1.0f) * scn.lightCount()));
}
