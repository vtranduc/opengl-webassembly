#include "../headers/preset.h"

void Preset::init() {
    preset.init();
}

void Preset::set(uint32_t code) {
    Name name = static_cast<Name>(code);
    switch(name) {
        case Name::ColorTriangle:
            preset.set();
            break;
        default: throw "Preset is not defined";
    }
}

void Preset::setUniform(UniformData data) {
    preset.setUniform(data.colorTriangle);
}

void Preset::render() {
    preset.render();
}