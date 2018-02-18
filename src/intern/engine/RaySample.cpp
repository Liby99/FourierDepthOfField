#include "engine/RaySample.h"

using namespace recartyar;

RaySample::RaySample(int i, int j, vec2 imgsp, vec2 aptsp) :
    i(i), j(j), imageSample(imgsp), apertureSample(aptsp) {}
