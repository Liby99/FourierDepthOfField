#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

namespace recartyar {
    class Ray {
    public:
        glm::vec3 origin;
        glm::vec3 direction;
        Ray();
        Ray(glm::vec3 origin, glm::vec3 direction);
        glm::vec3 getPoint(float t);
        void increment();
    };
};

#endif
