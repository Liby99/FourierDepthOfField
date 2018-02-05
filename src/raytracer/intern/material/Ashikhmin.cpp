#include "material/Ashikhmin.h"

const float Ashikhmin::DEFAULT_DIFFUSE_LEVEL = 1.0f;
const Color Ashikhmin::DEFAULT_DIFFUSE_COLOR = Color::WHITE;
const float Ashikhmin::DEFAULT_SPECULAR_LEVEL = 0.0f;
const Color Ashikhmin::DEFAULT_SPECULAR_COLOR = Color::BLACK;
const float Ashikhmin::DEFAULT_ROUGHNESS = 500.0f;

Ashikhmin::Ashikhmin() : Material() {
    setDiffuseLevel(DEFAULT_DIFFUSE_LEVEL);
    setDiffuseColor(DEFAULT_DIFFUSE_COLOR);
    setSpecularLevel(DEFAULT_SPECULAR_LEVEL);
    setSpecularColor(DEFAULT_SPECULAR_COLOR);
    setRoughness(DEFAULT_ROUGHNESS, DEFAULT_ROUGHNESS);
}

void Ashikhmin::setSampleMethod(int sm) {
    this->sampleMethod = sm;
}

void Ashikhmin::setWeightMethod(int wm) {
    this->weightMethod = wm;
}

void Ashikhmin::setDiffuseLevel(float level) {
    this->diffuseLevel = level;
}

float Ashikhmin::getDiffuseLevel() {
    return diffuseLevel;
}

void Ashikhmin::setDiffuseColor(Color color) {
    this->diffuseColor = color;
}

Color Ashikhmin::getDiffuseColor() {
    return diffuseColor;
}

void Ashikhmin::setSpecularLevel(float level) {
    this->specularLevel = level;
}

float Ashikhmin::getSpecularLevel() {
    return specularLevel;
}

void Ashikhmin::setSpecularColor(Color color) {
    this->specularColor = color;
}

Color Ashikhmin::getSpecularColor() {
    return specularColor;
}

void Ashikhmin::setRoughness(float u, float v) {
    setRoughnessU(u);
    setRoughnessV(v);
}

void Ashikhmin::setRoughnessU(float u) {
    this->roughnessU = u;
}

void Ashikhmin::setRoughnessV(float v) {
    this->roughnessV = v;
}

float Ashikhmin::getRoughnessU() {
    return roughnessU;
}

float Ashikhmin::getRoughnessV() {
    return roughnessV;
}

Color Ashikhmin::computeReflection(Intersection & i, Ray & out) {
    
    Ray & in = i.getRay();
    vec3 k1 = -in.getDirection();
    vec3 k2 = out.getDirection();
    vec3 n = i.getNormal();
    vec3 u = i.getTangentU();
    vec3 v = i.getTangentV();
    
    vec3 h = normalize(k1 + k2);
    
    float kh = dot(k2, h);
    float nk1 = dot(n, k1);
    float nk2 = dot(n, k2);
    float nh = dot(n, h);
    float hu = dot(h, u);
    float hv = dot(h, v);
    
    float f = specularLevel + (1.0f - specularLevel) * pow(1.0f - kh, 5.0f);
    
    float ps1 = sqrt((roughnessU + 1) * (roughnessV + 1)) / 8.0f;
    float ps2 = pow(nh, ((roughnessU * hu * hu + roughnessV * hv * hv) / (1.0f - nh * nh))) / (kh * fmax(nk1, nk2));
    float ps = ps1 * ps2 * f;
    if (specularLevel == 0.0f || ps != ps) {
        ps = 0.0f;
    }
    
    float pd1 = ((28.0f * diffuseLevel) / 23.0f) * (1.0f - specularLevel);
    float pd2 = 1.0f - pow(1.0f - 0.5f * nk1, 5.0f);
    float pd3 = 1.0f - pow(1.0f - 0.5f * nk2, 5.0f);
    float pd = pd1 * pd2 * pd3;
    if (pd != pd) {
        pd = 0.0f;
    }
    
    return specularColor * ps + diffuseColor * pd;
}

pair<Ray, Color> Ashikhmin::generateSample(Intersection & intersection, vec2 sample) {
    
    Ray & inray = intersection.getRay();
    vec3 pos = intersection.getPosition();
    vec3 normal = intersection.getNormal();
    vec3 tangentU = intersection.getTangentU();
    vec3 tangentV = intersection.getTangentV();
    vec3 indir = inray.getDirection();
    
    if (Sampler::random() < specularLevel) {
        
        // Calculate phi
        float phi = atan(sqrt((roughnessU + 1.0f) / (roughnessV + 1.0f)) * tan(pi * sample.x * 0.5f));
        float quadrant = Sampler::random();
        if (quadrant >= 0.75f) phi = 2.0f * pi - phi;
        else if (quadrant >= 0.5f) phi = pi + phi;
        else if (quadrant >= 0.25f) phi = pi - phi;
        
        float temp = roughnessU * pow(cos(phi), 2.0f) + roughnessV * pow(sin(phi), 2.0f);
        float cosTheta = pow(1.0f - sample.y, 1.0f / (temp + 1.0f));
        float sinTheta = sin(acos(cosTheta));
        vec3 h = normalize(normal * cosTheta + tangentU * sinTheta * cos(phi) + tangentV * sinTheta * sin(phi));
        
        // Calculate the reflection ray
        vec3 k1 = -indir;
        vec3 k2 = -k1 + 2.0f * dot(k1, h) * h;
        if (dot(k2, intersection.getNormal()) < 0.0f) {
            return make_pair(Ray(), Color::BLACK);
        }
        
        // float phh = sqrt((roughnessU + 1.0f) / (roughnessV + 1.0f)) / 2.0f * pow(dot(normal, h), temp);
        // float pk2 = phh / (4 * dot(k1, h));
        
        Ray ray = Ray(pos, k2, inray.getDepth() + 1);
        return make_pair(ray, specularColor * specularLevel);
    }
    else {
        
        // Diffuse part
        float s = sample.x;
        float t = sample.y;
        float u = 2.0f * pi * s;
        float v = sqrt(1.0f - t);
        
        vec3 dir = normalize(normal * sqrt(t) + tangentU * v * cos(u) + tangentV * v * sin(u));
        Ray ray = Ray(pos, dir, inray.getDepth() + 1);
        return make_pair(ray, diffuseColor * diffuseLevel);
    }
}

Color Ashikhmin::emission() {
    return Color::BLACK;
}
