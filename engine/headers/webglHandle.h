#pragma once

#include <iostream>
#include <emscripten/html5.h>
#include "utils.h"
#include <GLES3/gl3.h>
#include "shader.h"
#include "preset.h"
#include "presets/uniform.h"
#include <functional>

using namespace std;

class WebGLHandle {
    public:

    WebGLHandle() = default;

    int initialize(char* canvasId, int clearColor, int startingPreset);

    int usePreset(int presetCode);

    int command(const Preset::Command& command);

    int setPresetCallbacks(const Preset::CallbackData& data);

    int setClearColor(int color);

    struct webCallbacks {
        function<void(int color)> onClearColorChange;
    }webCallbacks;
    
    private:

    Preset preset;

    EmscriptenWebGLContextAttributes attrs;

    void setContextAttribute();

    struct {
        GLfloat color[3];
    }tmp;
};