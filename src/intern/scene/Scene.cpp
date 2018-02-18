#include "scene/Scene.h"

using namespace recartyar;

Scene::Scene() {};

void Scene::setBackground(Color & color) {
    background = color;
}

Color & Scene::getBackground() {
    return background;
}

Camera & Scene::getCamera() {
    return camera;
}

bool Scene::hasLight() {
    return lightCount() != 0;
}

int Scene::lightCount() {
    return lights.size();
}

void Scene::addLight(Light & light) {
    lights.push_back(&light);
}

Light & Scene::getLight(int i) {
    return *lights[i];
}

int Scene::objectCount() {
    return objects.size();
}

void Scene::addObject(Object & object) {
    objects.push_back(&object);
}

Object & Scene::getObject(int i) {
    return *objects[i];
}

bool Scene::intersect(Ray & ray, Intersection & itsct) {
    bool hit = false;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->intersect(ray, itsct)) {
            hit = true;
        }
    }
    return hit;
}
