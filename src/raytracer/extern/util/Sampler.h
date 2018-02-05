#ifndef SAMPLER_H
#define SAMPLER_H

#include "util/Random.h"
#include "util/Math.h"
#include <stdexcept>
#include <cstdint>
#include <climits>
#include <vector>

using namespace std;

class Sampler {
private:
    
    // Helper weighting methods
    static vec2 gaussianWeight(vec2 r);
    static vector<vec2> gaussianWeight(vector<vec2> v);
    
    // Shirley Weighting Methods
    static float shirley(float r);
    static vec2 shirleyWeight(vec2 r);
    static vector<vec2> shirleyWeight(vector<vec2> v);
    
public:
    
    const static int UNIFORM_SAMPLE = 0;
    const static int RANDOM_SAMPLE = 1;
    const static int JITTER_SAMPLE = 2;
    
    const static int NO_WEIGHT = 0;
    const static int GAUSSIAN_WEIGHT = 1;
    const static int SHIRLEY_WEIGHT = 2;
    
    static float random();
    static float random(uint32_t r);
    
    static vector<float> random1D(int amount);
    static vector<float> jitter1D(int amount);
    // vector<float> gaussianJitter1D(int amount);
    // vector<float> shirleyJitter1D(int amount);
    
    static vector<vec2> sample2D(int amount);
    static vector<vec2> sample2D(int amount, int sampleMethod);
    static vector<vec2> sample2D(int amount, int sampleMethod, int weightMethod);
    
    static vector<vec2> uniform2D(int amount);
    static vector<vec2> gaussianUniform2D(int amount);
    static vector<vec2> shirleyUniform2D(int amount);
    
    static vec2 random2D();
    static vec2 randomCircle();
    static vector<vec2> random2D(int amount);
    static vector<vec2> gaussianRandom2D(int amount);
    static vector<vec2> shirleyRandom2D(int amount);
    
    static vector<vec2> jitter2D(int amount);
    static vector<vec2> gaussianJitter2D(int amount);
    static vector<vec2> shirleyJitter2D(int amount);
};

#endif
