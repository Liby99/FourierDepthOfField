#include "engine/PathTracerBenchmark.h"

using namespace recartyar;

PathTracerBenchmark::PathTracerBenchmark(int spp) : PathTracer(spp) {}

void PathTracerBenchmark::render(Scene & scn, Image & img) {
    
    auto start = std::chrono::system_clock::now();
    
    std::cout << "Path Tracing " << getSampleAmount(img) << " samples..." << std::endl;
    
    PathTracer::render(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Path Trace Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

int PathTracerBenchmark::getSampleAmount(Image & img) {
    return img.width * img.height * mSpp;
}
