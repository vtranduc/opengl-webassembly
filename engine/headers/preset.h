#pragma once

#include <iostream>
#include "presets/colorTriangle.h"
#include "presets/triangleAssembly.h"

using namespace std;

class Preset {
public:
    enum class Name : uint32_t {
        ColorTriangle = 0,
        TriangleAssembly = 1
    }current;

    struct Command {
        Name type;
        CommandData data;
    };

    void init();

    void set(uint32_t code);

    void set(const Name name, const bool shouldRender = true);

    void command(const Command& command);

    void render(bool force = false);

    struct CallbackData {
        Name type;
        union Callbacks {
            ColorTriangle::Callbacks colorTriangle;
        }callbacks;
    };

    void setCallbacks(const CallbackData& data);
private:

    struct Presets {
        ColorTriangle colorTriangle;
        TriangleAssembly triangleAssembly;
    }presets;

    PresetBase* getCurrentPreset();

    PresetBase* getPreset(Name name);
};