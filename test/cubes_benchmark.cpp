#include <chrono>
#include <ctime>
#import <recartyar/recartyar.h>

using namespace recartyar;

class FDOFBenchmark : public FDOFTracer {
public:
    
    FDOFBenchmark(float k, float energy, float importance) : FDOFTracer(k) {
        this->energy = energy;
        this->importance = importance;
    }
    
    void render(Scene & scn, Image & img) {
        auto start = std::chrono::system_clock::now();
        
        FDOFTracer::render(scn, img);
        
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "FDOF Total Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    }
    
    void generateSamples(Scene & scn, Image & img, std::vector<RaySample> & samples) {
        auto start = std::chrono::system_clock::now();
        
        FDOFTracer::generateSamples(scn, img, samples);
        
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Generate Samples Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    }
    
    void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    
        std::cout << "Sample Amount: " << samples.size() << std::endl;
        
        auto start = std::chrono::system_clock::now();
        
        FDOFTracer::renderWithSample(scn, img, samples);
        
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Render Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;;
    }
    
    void postProcessing(Scene & scn, Image & img, std::vector<RaySample> & samples) {
        
        img.save("intermediate.bmp");
        
        auto start = std::chrono::system_clock::now();
        
        FDOFTracer::postProcessing(scn, img, samples);
        
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Reconstruction Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    }
};

class PathTracerBenchmark : public PathTracer {
public:
    PathTracerBenchmark(int spp) : PathTracer(spp) {}
    
    void render(Scene & scn, Image & img) {
        auto start = std::chrono::system_clock::now();
        
        PathTracer::render(scn, img);
        
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Path Trace Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    }
    
    void renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
        std::cout << "Sample Amount: " << samples.size() << std::endl;
        PathTracer::renderWithSample(scn, img, samples);
    }
};

int main() {
    
    PathTracerBenchmark pt(150);
    FDOFBenchmark ft(4, 20000, 50);
    
    Scene scn;
    scn.background = Color(0.5, 0.6, 0.8);
    scn.getCamera().setPosition(vec3(-0.1, 0.3, 2));
    scn.getCamera().setFocalDistance(2);
    scn.getCamera().setAperture(0.1);
    
    DirectLight dl;
    dl.color = Color(0.8, 0.8, 0.8);
    
    scn.addLight(dl);
    Lambert lbt(Color(0.8, 0.8, 0.8));
    
    std::vector<Cube *> cubes;
    for (int i = 0; i < 100; i++) {
        Cube * cube = new Cube(0.1, 0.1, 0.1);
        cube->setMaterial(lbt);
        float x = Sampler::random() * 4 - 2,
              y = Sampler::random() * 0.1 - 0.05,
              z = Sampler::random() * 4 - 2;
        cube->transform.setPosition(vec3(x, y, z));
        cube->transform.setRotation(vec3(Sampler::random(), Sampler::random(), Sampler::random()));
        scn.addObject(*cube);
        cubes.push_back(cube);
    }
    
    std::cout << "---------- FDOF TRACER ----------" << std::endl;
    
    Image fdofImage(640, 480);
    ft.render(scn, fdofImage);
    fdofImage.save("cubes_fdof.bmp");
    
    // std::cout << "---------- PATH TRACER ----------" << std::endl;
    //
    // Image ptImage(640, 480);
    // pt.render(scn, ptImage);
    // ptImage.save("cubes_path_trace.bmp");
    
    for (int i = 0; i < cubes.size(); i++) {
        delete cubes[i];
    }
}
