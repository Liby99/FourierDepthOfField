#include "engine/PathTracerBenchmark.h"

using namespace recartyar;

PathTracerBenchmark::PathTracerBenchmark(int spp) : PathTracer(spp) {}

void PathTracerBenchmark::render(Scene & scn, Image & img) {
    
    auto start = std::chrono::system_clock::now();
    
    PathTracer::render(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Path Trace Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void PathTracerBenchmark::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    
    std::cout << "Sample Amount: " << samples.size() << std::endl;
    
    PathTracer::renderWithSample(scn, img, samples);
}
