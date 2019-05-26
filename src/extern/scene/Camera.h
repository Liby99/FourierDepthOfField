#ifndef CAMERA_H
#define CAMERA_H

#include "utility/Ray.h"

namespace fdof {
    class Camera {
    protected:
        vec3 mPosition;
        vec3 mTarget;
        vec3 mUp;
        float mAspect;
        float mFovy;
        float mFocalDistance;
        float mAperture;
    public:
        Camera();
        Camera(vec3 position, vec3 target);
        vec3 position() const;
        void setPosition(vec3 p);
        vec3 target() const;
        void setTarget(vec3 t);
        float aspect() const;
        void setAspect(float a);
        float fovy() const;
        void setFovy(float f);
        float focalDistance() const;
        void setFocalDistance(float f);
        float aperture() const;
        void setAperture(float a);
        Ray getRay(const vec2 & screenSample) const;
        Ray getRay(const vec2 & screenSample, const vec2 & apertureSample) const;
    };
}

#endif
