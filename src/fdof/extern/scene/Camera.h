#ifndef CAMERA_H
#define CAMERA_H

#include "utility/Ray.h"

namespace fdof {
    class Camera {
    public:
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 up;
        float aspect;
        float fovy;
        float focalDistance;
        float aperture;
        Camera();
        Camera(glm::vec3 position, glm::vec3 target);
        Ray getRay(glm::vec2 & screenSample, glm::vec2 & apertureSample);
    };
}

#endif
