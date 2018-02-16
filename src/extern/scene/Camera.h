#ifndef CAMERA_H
#define CAMERA_H

#include "utility/Ray.h"

namespace recartyar {
    class Camera {
    public:
        vec3 position;
        vec3 target;
        vec3 up;
        float aspect;
        float fovy;
        float focalDistance;
        float aperture;
        Camera();
        Camera(vec3 position, vec3 target);
        Ray getRay(vec2 & screenSample, vec2 & apertureSample);
    };
}

#endif
