#include "scene/Scene.h"
#include "engine/RenderEngine.h"

Scene::Scene() {}

void Scene::setRenderEngine(RenderEngine & engine) {
    engine.setScene(*this);
    this->engine = &engine;
}

Color Scene::getBackgroundColor() {
    return background;
}

void Scene::setBackgroundColor(Color color) {
    this->background = color;
}

bool Scene::hasLight() {
    return lights.size() > 0;
}

unsigned int Scene::lightAmount() {
    return lights.size();
}

Light & Scene::getLight(int i) {
    return *(lights[i]);
}

void Scene::addLight(Light & light) {
    
    // First add light
    lights.push_back(&light);
    
    // Add Object if cast success
    Object * objptr = dynamic_cast<Object *>(&light);
    if (objptr) {
        addObject(*objptr);
    }
}

bool Scene::hasObject() {
    return objects.size() > 0;
}

unsigned int Scene::objectAmount() {
    return objects.size();
}

Object & Scene::getObject(int i) {
    return *(objects[i]);
}

void Scene::addObject(Object & object) {
    objects.push_back(&object);
}

bool Scene::getIntersection(Ray & ray, Intersection & intersection, float t) {
    bool hit = false;
    #pragma omp parallel for
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->intersect(ray, intersection, t)) {
            hit = true;
        }
    }
    return hit;
}

Color Scene::getRayColor(Ray & ray, float t) {
    Intersection intersection = Intersection(ray);
    if (getIntersection(ray, intersection, t)) {
        return engine->getColor(intersection, t);
    }
    else {
        return background;
    }
}
