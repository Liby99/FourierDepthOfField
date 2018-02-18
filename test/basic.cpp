#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    PathTracer pt;
    Scene scn;
    scn.getCamera().position = vec3(3, 1, 5);
    Cube cube;
    scn.addObject(cube);
    Cube flr(5, 0.01, 5);
    flr.transform.position = vec3(0, -0.5, 0);
    scn.addObject(flr);
    Image img(640, 480);
    pt.render(scn, img);
    img.save("depthtest.bmp");
    system("open depthtest.bmp");
}
