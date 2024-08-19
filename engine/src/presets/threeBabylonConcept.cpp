#include "../../headers/presets/threeBabylonConcept.h"

void ThreeBabylonConcept::init() {
    Mesh* sphere = new Mesh(Geometries::Sphere,  Materials::Mono);
    scene.add(*sphere);
    float position[3] = { 1.0f, 1.0f, 1.0f };
    float target[3] = { 0.0f, 0.0f, 0.0f };
    scene.getCamera().setPosition(position);
    scene.getCamera().lookAt(target);
};

void ThreeBabylonConcept::set() { setDirty(); };

void ThreeBabylonConcept::cleanUp() {};

void ThreeBabylonConcept::command(const CommandData& data) {};

void ThreeBabylonConcept::render() {
    PresetBase::render();
    scene.render();
};