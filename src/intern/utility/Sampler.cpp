#include "utility/Sampler.h"

using namespace fdof;

vec2 Sampler::gaussianWeight(vec2 r) {
    float a = 0.4f * sqrt(-2.0f * log(r.x));
    float b = 2.0f * pi * r.y;
    return vec2(0.5 + a * sin(b), 0.5 + a * cos(b));
}

std::vector<vec2> Sampler::gaussianWeight(std::vector<vec2> v) {
    for (int i = 0; i < v.size(); i++) {
        v[i] = gaussianWeight(v[i]);
    }
    return v;
}

float Sampler::shirley(float r) {
    if (r < 0.5) {
        return -0.5 + sqrt(2 * r);
    }
    else {
        return 1.5 - sqrt(2 - 2 * r);
    }
}

vec2 Sampler::shirleyWeight(vec2 r) {
    return vec2(shirley(r.x), shirley(r.y));
}

std::vector<vec2> Sampler::shirleyWeight(std::vector<vec2> v) {
    for (int i = 0; i < v.size(); i++) {
        v[i] = shirleyWeight(v[i]);
    }
    return v;
}

float Sampler::random() {
    uint64_t r = Random::next();
    return random(r);
}

float Sampler::random(uint32_t r) {
    return (float) r / UINT_MAX;
}

std::vector<float> Sampler::random1D(int amount) {
    std::vector<float> result;
    for (int i = 0; i < amount; i++) {
        result.push_back(Sampler::random());
    }
    return result;
}

std::vector<float> Sampler::jitter1D(int amount) {
    std::vector<float> result;
    float interval = 1.0f / amount;
    for (int i = 0; i < amount; i++) {
        result.push_back(interval * (i + Sampler::random()));
    }
    return result;
}

std::vector<vec2> Sampler::sample2D(int amount) {
    return uniform2D(amount);
}

std::vector<vec2> Sampler::sample2D(int amount, int sampleMethod) {
    switch (sampleMethod) {
        case UNIFORM_SAMPLE: return uniform2D(amount);
        case RANDOM_SAMPLE: return random2D(amount);
        case JITTER_SAMPLE: return jitter2D(amount);
        default: throw std::invalid_argument("Non-Existing Sampling Method");
    }
}

std::vector<vec2> Sampler::sample2D(int amount, int sampleMethod, int weightMethod) {
    switch (sampleMethod) {
        case UNIFORM_SAMPLE:
            switch (weightMethod) {
                case NO_WEIGHT: return uniform2D(amount);
                case GAUSSIAN_WEIGHT: return gaussianUniform2D(amount);
                case SHIRLEY_WEIGHT: return shirleyUniform2D(amount);
                default: throw std::invalid_argument("Non-Existing Weighting Method");
            }
            break;
        case RANDOM_SAMPLE:
            switch (weightMethod) {
                case NO_WEIGHT: return random2D(amount);
                case GAUSSIAN_WEIGHT: return gaussianRandom2D(amount);
                case SHIRLEY_WEIGHT: return shirleyRandom2D(amount);
                default: throw std::invalid_argument("Non-Existing Weighting Method");
            }
            break;
        case JITTER_SAMPLE:
            switch (weightMethod) {
                case NO_WEIGHT: return jitter2D(amount);
                case GAUSSIAN_WEIGHT: return gaussianJitter2D(amount);
                case SHIRLEY_WEIGHT: return shirleyJitter2D(amount);
                default: throw std::invalid_argument("Non-Existing Weighting Method");
            }
            break;
        default: throw std::invalid_argument("Non-Existing Sampling Method");
    }
}

std::vector<vec2> Sampler::uniform2D(int amount) {
    std::vector<vec2> result;
    int side = ceil(sqrt(amount));
    float interval = 1.0f / side;
    for (int x = 0; x < side; x++) {
        for (int y = 0; y < side; y++) {
            result.push_back(vec2(interval * (x + 0.5f), interval * (y + 0.5f)));
        }
    }
    return result;
}

std::vector<vec2> Sampler::gaussianUniform2D(int amount) {
    return gaussianWeight(uniform2D(amount));
}

std::vector<vec2> Sampler::shirleyUniform2D(int amount) {
    return shirleyWeight(uniform2D(amount));
}

vec2 Sampler::random2D() {
    uint64_t r = Random::next();
    uint32_t a = r >> 32;
    uint32_t b = r << 32 >> 32;
    return vec2(random(a), random(b));
}

vec2 Sampler::randomCircle() {
    vec2 s = random2D();
    float a = s.x * 2 * pi;
    float r = sqrt(s.y);
    return vec2(r * cos(a), r * sin(a));
}

std::vector<vec2> Sampler::random2D(int amount) {
    std::vector<vec2> result;
    for (int i = 0; i < amount; i++) {
        result.push_back(random2D());
    }
    return result;
}

std::vector<vec2> Sampler::gaussianRandom2D(int amount) {
    return gaussianWeight(random2D(amount));
}

std::vector<vec2> Sampler::shirleyRandom2D(int amount) {
    return shirleyWeight(random2D(amount));
}

std::vector<vec2> Sampler::jitter2D(int amount) {
    std::vector<vec2> result;
    int side = ceil(sqrt(amount));
    float interval = 1.0f / side;
    for (int x = 0; x < side; x++) {
        for (int y = 0; y < side; y++) {
            vec2 r = random2D();
            result.push_back(vec2(interval * (x + r.x), interval * (y + r.y)));
        }
    }
    return result;
}

std::vector<vec2> Sampler::gaussianJitter2D(int amount) {
    return gaussianWeight(jitter2D(amount));
}

std::vector<vec2> Sampler::shirleyJitter2D(int amount) {
    return shirleyWeight(jitter2D(amount));
}
