#pragma once

// #define build_number "@BUILD_NUMBER@";

#include <emscripten/html5.h>
#include "utils.h"
#include <GLES3/gl3.h>
#include <iostream>

#include <fstream>




// #include <glm/glm.hpp>
#include "/usr/include/glm/glm.hpp"

using namespace std;

using namespace glm;

class WebGLHandle {
    public:

    WebGLHandle() = default;

    int initialize(char* canvasId, int clearColor);

    int setClearColor(int color);

    private:

    EmscriptenWebGLContextAttributes attrs;

    void setContextAttribute();
};