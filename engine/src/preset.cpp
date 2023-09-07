#include "../headers/preset.h"

void Preset::init() {
    presets.colorTriangle.init();
    presets.triangleAssembly.init();
}

void Preset::set(uint32_t code) {
    current = static_cast<Name>(code);
    getCurrentPreset()->set();
    if (getCurrentPreset()->isDirty()) getCurrentPreset()->render();
}

void Preset::command(const CommandData& data) {
    getCurrentPreset()->command(data);
    if (getCurrentPreset()->isDirty())  getCurrentPreset()->render();
}

PresetBase* Preset::getCurrentPreset() {
    switch(current) {
        case Name::ColorTriangle:
            return &(presets.colorTriangle);
        case Name::TriangleAssembly:
            return &(presets.triangleAssembly);
        default:
            throw "Preset name is unhandled in getter";
    }
}