#ifndef FDOF_BENCHMARK_H
#define FDOF_BENCHMARK_H

#include <chrono>
#include <ctime>
#include "engine/FDOFTracer.h"

namespace recartyar {
    class FDOFBenchmark : public FDOFTracer {
    public:
        FDOFBenchmark(float k, float energy, float importance);
        void render(Scene & scn, Image & img) override;
        void preProcessing(Scene & scn, Image & img) override;
        void renderWithSample(Scene & scn, Image & img) override;
        void postProcessing(Scene & scn, Image & img) override;
        int getSampleAmount();
    };
}

#endif
