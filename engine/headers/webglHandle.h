#pragma once

#include <emscripten/html5.h>
#include "utils.h"
#include <GLES3/gl3.h>
#include "shader.h"
#include "preset.h"
#include <iostream>

using namespace std;

class WebGLHandle {
    public:

    WebGLHandle() = default;

    int initialize(char* canvasId, int clearColor);

    int setUniform(Preset::UniformData data);

    int setClearColor(int color);

    private:

    Preset preset;

    EmscriptenWebGLContextAttributes attrs;

    void setContextAttribute();
};