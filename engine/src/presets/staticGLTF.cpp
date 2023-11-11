#include "../../headers/presets/staticGLTF.h"

void StaticGLTF::init() {};

void StaticGLTF::set() {
    setDirty();
};

void StaticGLTF::command(const CommandData& data) {};

void StaticGLTF::render() {
    PresetBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void StaticGLTF::setCallbacks(const Callbacks& callbacks) {};