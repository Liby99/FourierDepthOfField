#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    PathTracer pt;
    pt.setSuperSampling(100);
    Scene scn;
    scn.getCamera().setPosition(vec3(-3, 1, 5));
    scn.getCamera().setFocalDistance(6);
    scn.getCamera().setAperture(0.1);
    DirectLight dl;
    scn.addLight(dl);
    Lambert lbt;
    Cube cube;
    cube.setMaterial(lbt);
    scn.addObject(cube);
    Cube flr(5, 0.01, 5);
    flr.transform.setPosition(vec3(0, -0.5, 0));
    flr.setMaterial(lbt);
    scn.addObject(flr);
    Image img(640, 480);
    pt.render(scn, img);
    img.save("depthtest.bmp");
    system("open depthtest.bmp");
}
