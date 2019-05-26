#include <fdof/fdof.h>

using namespace fdof;

int main() {
    Spectrum spctm(100);
//    spctm.saveImage("0_initial.bmp");
//    spctm.transport(3);
//    spctm.saveImage("1_after_transport.bmp");
//    spctm.occlude(0.2);
//    spctm.saveImage("2_after_occlusion.bmp");
//    spctm.transport(-3);
    std::cout << spctm.getVariance(3) << std::endl;
}
