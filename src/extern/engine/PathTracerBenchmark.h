#ifndef PATH_TRACER_BENCHMARK_H
#define PATH_TRACER_BENCHMARK_H

#include <chrono>
#include <ctime>

#include "engine/PathTracer.h"

namespace recartyar {
    class PathTracerBenchmark : public PathTracer {
    public:
        PathTracerBenchmark(int spp);
        void render(Scene & scn, Image & img) override;
        void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) override;
    };
}

#endif
