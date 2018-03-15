#include "engine/FDOFBenchmark.h"

using namespace recartyar;

FDOFBenchmark::FDOFBenchmark(float k, float energy, float importance) : FDOFTracer(k) {
    this->energy = energy;
    this->importance = importance;
}

void FDOFBenchmark::render(Scene & scn, Image & img) {
    
    std::cout << "Starting FDOF Render" << std::endl;
    
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::render(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "FDOF Total Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void FDOFBenchmark::preProcessing(Scene & scn, Image & img) {
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::preProcessing(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Pre Processing Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Generated " << getSampleAmount() << " samples" << std::endl;
}

void FDOFBenchmark::renderWithSample(Scene & scn, Image & img) {
    
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::renderWithSample(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Render Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void FDOFBenchmark::postProcessing(Scene & scn, Image & img) {
    
    img.save("intermediate.bmp");
    
    auto start = std::chrono::system_clock::now();
    
    FDOFTracer::postProcessing(scn, img);
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Reconstruction Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

int FDOFBenchmark::getSampleAmount() {
    int counter = 0;
    for (int p = 0; p < samplingPoints.size(); p++) {
        quasisampler::Point2D & pt = samplingPoints[p];
        int x = int(pt.x), y = int(pt.y);
        counter += int(lensDensity.getColor(x, y).r);
    }
    return counter;
}
