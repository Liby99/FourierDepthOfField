#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    PathTracer pt;
    Scene scn;
    scn.getCamera().position = vec3(0, 0, 5);
    Cube cube;
    scn.addObject(cube);
    Image img(640, 480);
    pt.render(scn, img);
    img.save("depthtest.bmp");
}
