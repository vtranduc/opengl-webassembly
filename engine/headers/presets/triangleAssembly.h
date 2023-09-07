#pragma once

#include <GLES3/gl3.h>
#include "presetBase.h"
#include "../utils.h"
#include "../shader.h"

#include <iostream>

using namespace std;

class TriangleAssembly : public PresetBase {
    public:

    void init() override;

    void set() override;

    void command(const CommandData& data) override;

    void render() override;

    private:

    const float vertices[9] = {
        -0.5f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    GLuint program;

    struct {
        GLfloat color[3];
    }tmp;
};