#include "material/Luminance.h"

Luminance::Luminance() : Luminance(Color::WHITE) {}

Luminance::Luminance(Color color) : Luminance(color, 1) {}

Luminance::Luminance(Color color, float intensity) : Material() {
    setColor(color);
    setIntensity(intensity);
}

Color Luminance::getColor() {
    return color;
}

void Luminance::setColor(Color color) {
    this->color = color;
}

float Luminance::getIntensity() {
    return intensity;
}

void Luminance::setIntensity(float intensity) {
    this->intensity = intensity;
}

Color Luminance::emission() {
    return color * intensity;
}
