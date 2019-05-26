#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "utility/Math.h"
#include <glm/gtc/matrix_transform.hpp>

namespace fdof {
    class Transform {
    private:
        bool mCached;
        mat4 mCache;
        vec3 mPosition;
        vec3 mRotation;
        vec3 mScale;
    public:
        Transform();
        void translate(vec3 trans);
        void setPosition(vec3 p);
        void scale(vec3 s);
        void setScale(vec3 s);
        void rotate(vec3 r);
        void setRotation(vec3 r);
        vec3 position();
        vec3 rotation();
        vec3 scale();
        mat4 getTransform();
    private:
        mat4 getTranslateMatrix();
        mat4 getRotateXMatrix();
        mat4 getRotateYMatrix();
        mat4 getRotateZMatrix();
        mat4 getRotateMatrix();
        mat4 getScaleMatrix();
    };
}

#endif
