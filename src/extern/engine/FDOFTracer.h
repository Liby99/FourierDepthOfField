#ifndef FDOF_TRACER_H
#define FDOF_TRACER_H

#include "engine/PathTracer.h"
#include "engine/SpatialDensitySampler.h"
#include "utility/Spectrum.h"

namespace recartyar {
    class FDOFTracer : public PathTracer {
    private:
        class Tile {
        public:
            vec2 upperLeft, bottomRight;
            Tile * up, right, bottom, left;
            std::vector<
            Tile(vec2 upperLeft, vec2 bottomRight);

        };
    public:
        float k, energy, importance;
        std::vector<int> cocs;
        FDOFTracer();
        explicit FDOFTracer(float k);
        void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) override;
        void postProcessing(Scene &scn, Image &img, std::vector<RaySample> &samples) override;
    protected:
        void generatePrimaryRays(Scene &scn, Image &img, std::vector<RaySample> &samples);
        void traceIntersections(Scene & scn, std::vector<RaySample> & samples, std::vector<Intersection> & itscts);
        float getCircleOfConfusion(Camera & cam, Intersection & itsct);
        void traceCircleOfConfusion(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs);
        bool checkOcclusion(Camera & cam, Intersection & i1, Intersection & i2);
        void propagateSpectra(Scene & scn, Image & img, std::vector<Intersection> & itscts, std::vector<int> & cocs, Image & spatialDensity, Image & lensDensity);
        static float gaussianWeight(float d, float variance);
    };
}

#endif
