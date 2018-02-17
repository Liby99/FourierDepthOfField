#include "utility/Random.h"

using namespace recartyar;

uint64_t Random::s = DEFAULT_SEED;
uint64_t Random::cs = DEFAULT_SEED;

void Random::seed(int input) {
    s = input;
    cs = input;
}

void Random::reset() {
    cs = s;
}

uint64_t Random::next() {
    cs ^= cs >> 21;
    cs ^= cs << 35;
    cs ^= cs >> 4;
    return cs;
}
