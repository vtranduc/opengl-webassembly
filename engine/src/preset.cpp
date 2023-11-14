#include "../headers/preset.h"

void Preset::init() {
    presets.colorTriangle.init();
    presets.triangleAssembly.init();
    presets.staticGLTF.init();
}

void Preset::set(uint32_t code) {
    set(static_cast<Name>(code));
}

void Preset::set(const Name name, const bool shouldRender) {
    if (name == current) return;
    current = name;
    getCurrentPreset()->set();
    if (shouldRender) render();
}

void Preset::command(const Command& command) {
    const Name currentPreset = current;
    set(command.type, false);
    getPreset(command.type)->command(command.data);
    set(currentPreset, false);
    render();
}

void Preset::render(bool force) { if (force || getCurrentPreset()->isDirty())  getCurrentPreset()->render(); }

PresetBase* Preset::getCurrentPreset() {
    return getPreset(current);
}

PresetBase* Preset::getPreset(Name name) {
    switch(name) {
    case Name::ColorTriangle: return &(presets.colorTriangle);
    case Name::TriangleAssembly: return &(presets.triangleAssembly);
    case Name::StaticGLTF: return &(presets.staticGLTF);
    default: throw "Preset name is unhandled in getter";
    }
}

void Preset::setCallbacks(const CallbackData& data) {
    switch(data.type) {
        case Name::ColorTriangle:
            presets.colorTriangle.setCallbacks(data.callbacks.colorTriangle);
            break;
        case Name::TriangleAssembly:
            presets.triangleAssembly.setCallbacks(data.callbacks.triangleAssembly);
            break;
        case Name::StaticGLTF:
            presets.staticGLTF.setCallbacks(data.callbacks.staticGLTF);
            break;
        default:
            throw "Callback type not handled";
    }
}
