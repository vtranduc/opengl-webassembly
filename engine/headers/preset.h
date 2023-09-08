#pragma once

#include <iostream>
#include "presets/colorTriangle.h"
#include "presets/triangleAssembly.h"

using namespace std;

class Preset {
    public:

    void init();

    void set(uint32_t code);

    void command(const CommandData& data);

    void render(bool force = false);

    private:

    struct Presets {
        ColorTriangle colorTriangle;
        TriangleAssembly triangleAssembly;
    }presets;

    PresetBase* getCurrentPreset();

    public:

    enum class Name : uint32_t {
        ColorTriangle = 0,
        TriangleAssembly = 1
    }current;

    struct CallbackData {
        Name type;
        union Callbacks {
            ColorTriangle::Callbacks colorTriangle;
        }callbacks;
    };

    void setCallbacks(const CallbackData& data);
};