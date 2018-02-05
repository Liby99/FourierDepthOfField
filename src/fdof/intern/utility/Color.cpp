#include "utility/Color.h"

using namespace fdof;

const float Color::MAX = 255.0f;
const float Color::DEFAULT_R = 0;
const float Color::DEFAULT_G = 0;
const float Color::DEFAULT_B = 0;

const Color Color::WHITE = Color(1, 1, 1);
const Color Color::BLACK = Color();
const Color Color::RED = Color(1, 0, 0);
const Color Color::GREEN = Color(0, 1, 0);
const Color Color::BLUE = Color(0, 0, 1);

float bound(float f) {
    return (f <= 0) ? 0 : (f >= 1) ? 1 : f;
}

Color::Color() : Color(DEFAULT_R, DEFAULT_G, DEFAULT_B) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

float Color::getR() {
    return r;
}

float Color::getG() {
    return g;
}

float Color::getB() {
    return b;
}

int Color::getIntR() {
    return int(bound(r) * MAX) & 0xff;
}

int Color::getIntG() {
    return int(bound(g) * MAX) & 0xff;
}

int Color::getIntB() {
    return int(bound(b) * MAX) & 0xff;
}

void Color::setR(float r) {
    this->r = r;
}

void Color::setG(float g) {
    this->g = g;
}

void Color::setB(float b) {
    this->b = b;
}

int Color::toInt() {
    return (getIntR() << 16) | (getIntG() << 8) | getIntB();
}

Color Color::operator+(Color c) {
    return Color(r + c.r, g + c.g, b + c.b);
}

Color & Color::operator+=(Color c) {
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

Color Color::operator-(Color c) {
    return Color(r - c.r, g - c.g, b - c.b);
}

Color & Color::operator-=(Color c) {
    r = r - c.r;
    g = g - c.g;
    b = b - c.b;
    return *this;
}

Color Color::operator*(Color c) {
    return Color(r * c.r, g * c.g, b * c.b);
}

Color & Color::operator*=(Color c) {
    r *= c.r;
    g *= c.g;
    b *= c.b;
    return *this;
}

Color Color::operator*(float scale) {
    return Color(r * scale, g * scale, b * scale);
}

Color & Color::operator*=(float scale) {
    r *= scale;
    g *= scale;
    b *= scale;
    return *this;
}

Color Color::operator/(int count) {
    return Color(r / count, g / count, b / count);
}

Color & Color::operator/=(int count) {
    r /= count;
    g /= count;
    b /= count;
    return *this;
}

Color::operator std::string() {
    return "rgb(" + std::to_string(getIntR()) + ", " + std::to_string(getIntG()) + ", " + std::to_string(getIntB()) + ")";
}

Color Color::parse(int c) {
    int r = (float) ((c >> 16) & 0xff) / MAX;
    int g = (float) ((c >> 8) & 0xff) / MAX;
    int b = (float) (c & 0xff) / MAX;
    return Color(r, g, b);
}

bool Color::operator==(const Color & c) const {
    return r == c.r && g == c.g && b == c.b;
}

bool Color::operator!=(const Color & c) const {
    return r != c.r || g != c.g || b != c.b;
}

std::ostream & operator<< (std::ostream & stream, Color & color) {
    stream << (std::string)color;
    return stream;
}
