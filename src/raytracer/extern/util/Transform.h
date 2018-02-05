#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "util/Math.h"

class Transform {
public:
    static mat4 rotate(const float degrees, const vec3& axis);
    static mat4 scale(const float &sx, const float &sy, const float &sz);
    static mat4 translate(const float &tx, const float &ty, const float &tz);
};

#endif
