#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat2 mat2;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

const float pi = 3.14159265f;

float max(float a, float b, float c);
float min(float a, float b, float c);
int maxAxis(const vec3 & v);
vec3 maxVec(const vec3 & a, const vec3 & b);
vec3 minVec(const vec3 & a, const vec3 & b);

#endif
