#pragma once

#include <GLES3/gl3.h>
#include "presetBase.h"
#include "../utils.h"
#include "../shader.h"
#include "../math.h"

#include <iostream>

using namespace std;

class TriangleAssembly : public PresetBase {
    public:

    void init() override;

    void set() override;

    void command(const CommandData& data) override;

    void render() override;

    private:

    static constexpr int nTriangles = 12;

    const GLfloat vertices[nTriangles * 9] = {
        -0.5,-0.5,-0.5, // triangle 1 : begin
        -0.5,-0.5, 0.5,
        -0.5, 0.5, 0.5, // triangle 1 : end
        0.5, 0.5,-0.5, // triangle 2 : begin
        -0.5,-0.5,-0.5,
        -0.5, 0.5,-0.5, // triangle 2 : end
        0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        0.5,-0.5, 0.5,
        -0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5,-0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5,-0.5,
        -0.5, 0.5,-0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5,-0.5, 0.5
    };

    GLuint program;

    struct {
        GLfloat color[3];
    }tmp;
};