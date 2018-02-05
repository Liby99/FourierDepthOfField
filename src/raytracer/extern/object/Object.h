#ifndef OBJECT_H
#define OBJECT_H

#include "animation/Animatable.h"
#include "util/Transform.h"
#include "util/Ray.h"
#include "util/Intersection.h"
#include "util/BoundingBox.h"
#include "util/Sampler.h"
#include "material/Material.h"

#include <vector>

class Object {
protected:
    
    // Default Values
    const static vec3 DEFAULT_POSITION;
    const static vec3 DEFAULT_SCALER;
    const static vec3 DEFAULT_ROTATION;
    
    // Materials
    Material * material;
    
    BoundingBox * box;
    
    // Transform properties
    bool transformed;
    Animatable<vec3> position;
    Animatable<vec3> scaler;
    Animatable<vec3> rotation;
    
    // Virtual Functions
    virtual bool updateIntersect(Ray & ray, Intersection & intersection, float t);
    virtual vector<vec3> getBoundingVertices();
    virtual vec3 sampleSurfacePointHelper(float t);
    
public:
    
    // Constructor
    Object();
    ~Object();
    
    float surfaceArea;
    
    // Material Related
    bool hasMaterial();
    virtual Material & getMaterial();
    virtual void setMaterial(Material & material);
    
    // Basic Getter
    vec3 getRotation(float t);
    vec3 getScale(float t);
    vec3 getPosition(float t);
    
    // Rotate Transformation
    void setRotate(vec3 rotation);
    void rotate(vec3 rotation);
    void rotateX(float degX);
    void rotateY(float degY);
    void rotateZ(float degZ);
    void rotate(vec3 rotation, int t);
    void rotateX(float degX, int t);
    void rotateY(float degY, int t);
    void rotateZ(float degZ, int t);
    
    // Translate Transformation
    void setTranslate(vec3 rotation);
    void translate(vec3 position);
    void translateX(float x);
    void translateY(float y);
    void translateZ(float z);
    void translate(vec3 position, int t);
    void translateX(float x, int t);
    void translateY(float y, int t);
    void translateZ(float z, int t);
    
    // Scale Transformation
    void setScale(vec3 scaler);
    void scale(vec3 scaler);
    void scaleX(float scaleX);
    void scaleY(float scaleY);
    void scaleZ(float scaleZ);
    void scale(vec3 scaler, int t);
    void scaleX(float scaleX, int t);
    void scaleY(float scaleY, int t);
    void scaleZ(float scaleZ, int t);
    
    // Get transformation helper method
    mat4 getTransformMatrix(float t);
    
    // Random Sample a point on the surface
    vec3 sampleSurfacePoint(float t);
    
    // Get Bounding Box Helper Method
    BoundingBox getBoundingBox(float t);
    
    // Virtaul intersect method
    virtual bool intersect(Ray & ray, Intersection & intersection, float t);
};

#endif
