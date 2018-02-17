#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

namespace recartyar {
    class Random {
    private:
        static const uint64_t DEFAULT_SEED = 1234567;
        static uint64_t s;
        static uint64_t cs;
    public:
        static void seed(int input);
        static void reset();
        static uint64_t next();
    };
}

#endif
