#include <recartyar/recartyar.h>

using namespace recartyar;

int main() {
    
    FDOFBenchmark ft(10, 3000, 10);
    
    Scene scn;
    scn.background = Color(0.7, 0.8, 0.9);
    scn.getCamera().setPosition(vec3(-3, 2, 6));
    scn.getCamera().setFocalDistance(6);
    scn.getCamera().setAperture(0.1);
    DirectLight dl;
    dl.color = Color(0.8, 0.8, 0.8);
    scn.addLight(dl);
    Lambert lbt(Color(0.8));
    BoxTreeObject dragon("res/objects/dragon.ply");
    dragon.transform.setScale(vec3(20));
    dragon.transform.setPosition(vec3(0, -1.4, 0));
    dragon.setMaterial(lbt);
    scn.addObject(dragon);
    BoxTreeObject dragon2("res/objects/dragon.ply");
    dragon2.transform.setScale(vec3(20));
    dragon2.transform.setPosition(vec3(0, -1.4, 4));
    dragon2.setMaterial(lbt);
    scn.addObject(dragon2);
    Cube flr(10, 0.01, 10);
    flr.transform.setPosition(vec3(0, -0.5, 0));
    flr.setMaterial(lbt);
    scn.addObject(flr);
    
    Image img(640, 480);
    ft.render(scn, img);
    img.save("dragon.bmp");
    system("open dragon.bmp");
}
