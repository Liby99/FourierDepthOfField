#include "material/Dielectric.h"

const float Dielectric::DEFAULT_IOR = 1;
const float Dielectric::DEFAULT_ABSORPTION_COEF = 1;
const Color Dielectric::DEFAULT_ABSORPTION_COLOR = Color(1, 1, 1);
const Color Dielectric::DEFAULT_SPECULAR_COLOR = Color(1, 1, 1);

const float Dielectric::AIR_IOR = 1.0003;
const float Dielectric::WATER_IOR = 1.3333;
const float Dielectric::ICE_IOR = 1.309;
const float Dielectric::GLASS_IOR = 1.6;
const float Dielectric::DIAMOND_IOR = 2.42;

Dielectric::Dielectric() : Material() {
    setIor(DEFAULT_IOR);
    setAbsorptionCoef(DEFAULT_ABSORPTION_COEF);
    setAbsorptionColor(DEFAULT_ABSORPTION_COLOR);
    setSpecularColor(DEFAULT_SPECULAR_COLOR);
}

float Dielectric::getIor() {
    return ior;
}

void Dielectric::setIor(float ior) {
    this->ior = ior;
}

float Dielectric::getAbsorptionCoef() {
    return absorptionCoef;
}

void Dielectric::setAbsorptionCoef(float coef) {
    this->absorptionCoef = coef;
}

Color Dielectric::getAbsorptionColor() {
    return absorptionColor;
}

void Dielectric::setAbsorptionColor(Color c) {
    this->absorptionColor = c;
}

Color Dielectric::getSpecularColor() {
    return specularColor;
}

void Dielectric::setSpecularColor(Color c) {
    this->specularColor = c;
}

pair<Ray, Color> Dielectric::generateSample(Intersection & intersection, vec2 sample) {
    
    Ray & inray = intersection.getRay();
    
    float ni = AIR_IOR;
    float nt = ior;
    float absorption = 0.0f;
    
    if (inray.isInside()) {
        swap(ni, nt);
        absorption = absorptionCoef;
    }
    
    vec3 pos = intersection.getPosition();
    vec3 n = intersection.getNormal();
    vec3 d = inray.getDirection();
    float ndd = dot(n, d);
    if (ndd > 0) {
        n = -n;
        ndd = -ndd;
    }
    
    vec3 r = d - 2.0f * ndd * n;
    r = normalize(r);
    
    vec3 z = (d - ndd * n) * ni / nt;
    float z2 = length(z) * length(z);
    
    if (z2 >= 1.0f) {
        Ray reflect = Ray(pos, r, inray.getDepth() + 1, inray.isInside());
        return make_pair(reflect, specularColor);
    }
    
    vec3 t = z - sqrt(1.0f - z2) * n;
    t = normalize(t);
    
    float ndt = dot(n, t);
    float rPar = (nt * ndd - ni * ndt) / (nt * ndd + ni * ndt);
    float rPerp = (ni * ndd - nt * ndt) / (ni * ndd + nt * ndt);
    float fr = 0.5f * (rPar * rPar + rPerp * rPerp);
    
    Color color = Color::WHITE;
    if (absorption > 0.0f) {
        float s = -absorption * intersection.getDistanceToOrigin();
        color.setR(exp(s * (1.0f - absorptionColor.getR())));
        color.setG(exp(s * (1.0f - absorptionColor.getG())));
        color.setB(exp(s * (1.0f - absorptionColor.getB())));
    }
    
    if (Sampler::random() < fr) {
        Ray reflect = Ray(pos, r, inray.getDepth() + 1, inray.isInside());
        if (inray.isInside()) {
            return make_pair(reflect, color);
        }
        else {
            return make_pair(reflect, specularColor);
        }
    }
    else {
        Ray transmit = Ray(pos, t, inray.getDepth() + 1, !inray.isInside());
        return make_pair(transmit, color);
    }
}
