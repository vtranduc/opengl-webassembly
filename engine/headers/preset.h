#pragma once

#include "presets/colorTriangle.h"

class Preset {
    private:

    enum class Name : uint32_t {
        ColorTriangle = 0,
    };

    ColorTriangle preset;

    public:

    union UniformData {
        ColorTriangle::UniformDataIntType colorTriangle;
    };

    void init();

    void set(uint32_t code);

    void setUniform(UniformData data);

    void render();
};