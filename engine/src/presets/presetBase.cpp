#include "../../headers/presets/presetBase.h"

bool PresetBase::isDirty() const { return dirty; };

void PresetBase::setDirty() { dirty = true; };

void PresetBase::render() {
    cout << "render" << endl;
    dirty = false;
};
