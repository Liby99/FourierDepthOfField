#ifndef VERTEX_H
#define VERTEX_H

#include "utility/Transform.h"

namespace fdof {
    class Vertex {
    private:

        // Basic parameter for vertex
        vec3 position;
        vec3 normal;

    public:

        // Constructor
        Vertex();
        Vertex(vec3 position);
        Vertex(vec3 position, vec3 normal);

        // Basic getter and setter
        vec3 getPosition() ;
        void setPosition(vec3 position);
        void setPositionX(float x);
        void setPositionY(float y);
        void setPositionZ(float z);

        vec3 getNormal() ;
        void setNormal(vec3 normal);
        void setNormalX(float x);
        void setNormalY(float y);
        void setNormalZ(float z);

        void addUnnormalized(vec3 normal);
        void divideNormal(float num);
        void normalize();
    };
}

#endif
