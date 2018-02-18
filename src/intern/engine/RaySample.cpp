#include "engine/RaySample.h"

using namespace recartyar;

RaySample::RaySample(int i, int j, vec2 imgsp) : RaySample(i, j, imgsp, vec2(0, 0)) {}

RaySample::RaySample(int i, int j, vec2 imgsp, vec2 aptsp) : i(i), j(j), imageSample(imgsp), apertureSample(aptsp) {}
