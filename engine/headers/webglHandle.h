#pragma once

#include <emscripten/html5.h>
#include "utils.h"
#include <GLES3/gl3.h>
#include <iostream>

using namespace std;

class WebGLHandle {
    public:

    WebGLHandle() = default;

    int initialize(char* canvasId, int clearColor);

    int setClearColor(int color);

    private:

    EmscriptenWebGLContextAttributes attrs;

    void setContextAttribute();
};