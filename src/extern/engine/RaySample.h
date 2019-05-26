#ifndef RAY_SAMPLE_H
#define RAY_SAMPLE_H

#include "utility/Math.h"
#include "utility/Color.h"

namespace fdof {
    class RaySample {
    public:
        int i, j;
        vec2 imageSample, apertureSample;
        Color color;
        RaySample();
        RaySample(int i, int j, vec2 imgsp);
        RaySample(int i, int j, vec2 imgsp, vec2 aptsp);
    };
}

#endif
