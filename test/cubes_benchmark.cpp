#include <chrono>
#include <ctime>
#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    
    PathTracerBenchmark pt(200);
    FDOFBenchmark ft(50, 50000, 1);
    
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
    
    std::cout << "---------- PATH TRACER ----------" << std::endl;
    
    Image ptImage(640, 480);
    pt.render(scn, ptImage);
    ptImage.save("cubes_path_trace.bmp");
    
    for (int i = 0; i < cubes.size(); i++) {
        delete cubes[i];
    }
}
