#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "utility/Math.h"
#include <glm/gtc/matrix_transform.hpp>

namespace recartyar {
    class Transform {
    public:
        vec3 position;
        vec3 rotation;
        vec3 scale;
        Transform();
        mat4 getTranslateMatrix();
        mat4 getRotateXMatrix();
        mat4 getRotateYMatrix();
        mat4 getRotateZMatrix();
        mat4 getRotateMatrix();
        mat4 getScaleMatrix();
        mat4 getTransform();
    };
}

#endif
