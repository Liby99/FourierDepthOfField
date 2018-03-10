#include "engine/DiscontinuityTracer.h"

using namespace recartyar;

void DiscontinuityTracer::renderWithSample(Scene & scn, Image & img, std::vector<RaySample> & samples) {
    
    Image dtimg(img.width, img.height);
    depthTracer.render(scn, dtimg);
    
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            float c = 0;
            for (int x = i - 1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < dtimg.width && y >= 0 && y < img.height && hasDiscont(scn, dtimg, i, j, x, y)) {
                        c += 0.125;
                    }
                }
            }
            img.setColor(i, j, rgb(c));
        }
    }
}

bool DiscontinuityTracer::hasDiscont(Scene & scn, Image & depthImg, int i, int j, int x, int y) {
    float mainDepth = depthImg.getColor(i, j).r,
          nbDepth = depthImg.getColor(x, y).r;
    return abs(nbDepth - mainDepth) >= 0.01f;
}
