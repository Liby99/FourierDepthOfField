#include "engine/Engine.h"

using namespace fdof;

Engine::Engine() : Engine(640, 480) {};

Engine::Engine(int width, int height) : width(width), height(height) {};

Color Engine::getColor(Intersection & itsct) {
    return Color();
}

Image Engine::render(Scene & scn) {
    return Image(width, height);
}
