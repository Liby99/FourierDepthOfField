#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace fdof {
    class Transform {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        Transform();
        glm::mat4 getTranslateMatrix();
        glm::mat4 getRotateXMatrix();
        glm::mat4 getRotateYMatrix();
        glm::mat4 getRotateZMatrix();
        glm::mat4 getRotateMatrix();
        glm::mat4 getScaleMatrix();
        glm::mat4 getTransform();
    };
}

#endif
