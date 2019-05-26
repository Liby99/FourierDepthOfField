#ifndef FDOF_TRACER_H
#define FDOF_TRACER_H

#include "engine/PathTracer.h"
#include "engine/SpatialDensitySampler.h"
#include "utility/Spectrum.h"

namespace fdof {
    class FDOFTracer : public PathTracer {
    public:

        // FDOF Parameters
        float k, energy, importance;

    protected:

        // Generator used parameters
        int currP, currK, currNs;
        float hw, hh;
        Image lensDensity, spatialDensity;
        std::vector<quasisampler::Point2D> samplingPoints;
        std::vector<int> cocs;

    public:

        // Public override functions
        FDOFTracer();
        explicit FDOFTracer(float k);
        void preProcessing(Scene & scn, Image & img) override;
        void postProcessing(Scene & scn, Image & img) override;

    protected:

        // Generator methods
        void initiateGenerator(Scene & scn, Image & img) override;
        RaySample getNextSample(Scene & scn, Image & img) override;
        bool hasNextSample(Scene & scn, Image & img) override;

        // Helper prepass methods
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
