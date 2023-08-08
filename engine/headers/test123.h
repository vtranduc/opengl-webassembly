#include <iostream>
#include <GLES3/gl3.h>
#include "shader.h"
using namespace std;

static string getShaderSource(Shader::Vertex shader) {
    switch (static_cast<int>(shader)) {
        case 0: return
            "precision highp float;\n"
            "\n"
            "attribute vec3 position;\n"
            "\n"
            "void main() {\n"
            "    gl_Position = vec4(position, 1.0);\n"
            "}\n";
        default: return "";
    };
};

static string getShaderSource(Shader::Fragment shader) {
    switch (static_cast<int>(shader)) {
        case 0: return
            "precision highp float;\n"
            "\n"
            "uniform vec3 uColor;\n"
            "\n"
            "void main() {\n"
            "    gl_FragColor = vec4(uColor, 1.0);\n"
            "}\n";
        default: return "";
    };
};
