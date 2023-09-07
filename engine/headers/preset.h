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

    private:

    struct Presets {
        ColorTriangle colorTriangle;
        TriangleAssembly triangleAssembly;
    }presets;

    enum class Name : uint32_t {
        ColorTriangle = 0,
        TriangleAssembly = 1
    }current;

    PresetBase* getCurrentPreset();
};