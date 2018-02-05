#include "object/GridCloner.h"

void GridCloner::construct() {
    instances.clear();
    float hw = width / 2, hh = height / 2, hl = length / 2;
    float wseg = xCount > 1 ? width / (xCount - 1) : 0,
          hseg = yCount > 1 ? height / (yCount - 1) : 0,
          lseg = zCount > 1 ? length / (zCount - 1) : 0;
    for (int i = 0; i < xCount; i++) {
        for (int j = 0; j < yCount; j++) {
            for (int k = 0; k < zCount; k++) {
                vec3 position = vec3(-hw + i * wseg, -hh + j * hseg, -hl + k * lseg);
                InstanceObject * instance = new InstanceObject(*object);
                instance->translate(position);
                instances.push_back(instance);
            }
        }
    }
}

GridCloner::GridCloner(Object & object) : Cloner(object) {
    width = 1;
    height = 1;
    length = 1;
    xCount = 1;
    yCount = 1;
    zCount = 1;
    construct();
}

GridCloner::GridCloner(Object & object, float w, float h, float l, int x, int y, int z) : Cloner(object) {
    width = w;
    height = h;
    length = l;
    xCount = x;
    yCount = y;
    zCount = z;
    construct();
}

float GridCloner::getWidth() {
    return width;
}

float GridCloner::getHeight() {
    return height;
}

float GridCloner::getLength() {
    return length;
}

void GridCloner::setWidth(float width) {
    this->width = width;
    construct();
}

void GridCloner::setHeight(float height) {
    this->height = height;
    construct();
}

void GridCloner::setLength(float length) {
    this->length = length;
    construct();
}

int GridCloner::getXCount() {
    return xCount;
}

int GridCloner::getYCount() {
    return yCount;
}

int GridCloner::getZCount() {
    return zCount;
}

void GridCloner::setXCount(int xCount) {
    this->xCount = xCount;
    construct();
}

void GridCloner::setYCount(int yCount) {
    this->yCount = yCount;
    construct();
}

void GridCloner::setZCount(int zCount) {
    this->zCount = zCount;
    construct();
}
