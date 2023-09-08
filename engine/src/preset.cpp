#include "../headers/preset.h"

void Preset::init() {
    presets.colorTriangle.init();
    presets.triangleAssembly.init();
}

void Preset::set(uint32_t code) {
    current = static_cast<Name>(code);
    getCurrentPreset()->set();
    render();
}

void Preset::command(const CommandData& data) {
    getCurrentPreset()->command(data);
    render();
}

void Preset::render(bool force) { if (force || getCurrentPreset()->isDirty())  getCurrentPreset()->render(); }

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

void Preset::setCallbacks(const CallbackData& data) {
    switch(data.type) {
        case Name::ColorTriangle:
            presets.colorTriangle.setCallbacks(data.callbacks.colorTriangle);
            break;
        case Name::TriangleAssembly:
            break;
        default:
            throw "Callback type not handled";
    }
}
