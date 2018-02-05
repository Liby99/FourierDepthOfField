#include "util/Transform.h"

float max(float a, float b, float c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

float min(float a, float b, float c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int maxAxis(const vec3 & v) {
    return v.x > v.y ? (v.x > v.z ? 0 : 2) : (v.y > v.z ? 1 : 2);
}

vec3 maxVec(const vec3 & a, const vec3 & b) {
    return vec3(glm::max(a.x, b.x), glm::max(a.y, b.y), glm::max(a.z, b.z));
}

vec3 minVec(const vec3 & a, const vec3 & b) {
    return vec3(glm::min(a.x, b.x), glm::min(a.y, b.y), glm::min(a.z, b.z));
}

mat4 Transform::rotate(const float degrees, const vec3& axis) {
    float x = axis.x,
        y = axis.y,
        z = axis.z,
        cosine = cos(degrees / 180 * pi),
        sine = sin(degrees / 180 * pi),
        a = cosine + x * x * (1 - cosine),
        b = x * y * (1 - cosine) - z * sine,
        c = x * z * (1 - cosine) + y * sine,
        d = y * x * (1 - cosine) + z * sine,
        e = cosine + y * y * (1 - cosine),
        f = y * z * (1 - cosine) - x * sine,
        g = z * x * (1 - cosine) - y * sine,
        h = z * y * (1 - cosine) + x * sine,
        i = cosine + z * z * (1 - cosine);
    return mat4(a, d, g, 0, b, e, h, 0, c, f, i, 0, 0, 0, 0, 1);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) {
    return mat4(sx, 0, 0, 0,
                0, sy, 0, 0,
                0, 0, sz, 0,
                0, 0, 0, 1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) {
    return mat4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                tx, ty, tz, 1);
}
