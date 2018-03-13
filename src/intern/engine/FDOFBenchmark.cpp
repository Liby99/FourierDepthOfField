#include "engine/FDOFBenchmark.h"

using namespace recartyar;

FDOFBenchmark::FDOFBenchmark(float k, float energy, float importance) : FDOFTracer(k) {
    this->energy = energy;
    this->importance = importance;
}

void FDOFBenchmark::render(Scene & scn, Image & img) {
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::render(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "FDOF Total Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void FDOFBenchmark::generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::generateSamples(scn, img, samples);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Generate Samples Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void FDOFBenchmark::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {

    std::cout << "Sample Amount: " << samples.size() << std::endl;
    
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::renderWithSample(scn, img, samples);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Render Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void FDOFBenchmark::postProcessing(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    
    img.save("intermediate.bmp");
    
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::postProcessing(scn, img, samples);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Reconstruction Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}
