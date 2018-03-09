#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    PathTracer pt;
    pt.setSuperSampling(25);
    Scene scn;
    scn.background = Color(0.5, 0.6, 0.8);
    scn.getCamera().setPosition(vec3(0, 0.3, 2));
    scn.getCamera().setFocalDistance(2);
    scn.getCamera().setAperture(0.1);
    DirectLight dl;
    dl.color = Color(0.8, 0.8, 0.8);
    scn.addLight(dl);
    Lambert lbt(Color(0.3, 0.3, 0.4));
    
    std::vector<Cube *> cubes;
    for (int i = 0; i < 100; i++) {
        Cube * cube = new Cube(0.1, 0.1, 0.1);
        cube->setMaterial(lbt);
        float x = Sampler::random() * 4 - 2,
              y = Sampler::random() * 0.1 - 0.05,
              z = Sampler::random() * 4 - 2;
        cube->transform.setPosition(vec3(x, y, z));
        scn.addObject(*cube);
        cubes.push_back(cube);
    }
    
    Image img(640, 480);
    pt.render(scn, img);
    img.save("cubes.bmp");
    system("open cubes.bmp");
    
    for (int i = 0; i < cubes.size(); i++) {
        delete cubes[i];
    }
}
