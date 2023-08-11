#pragma once

#include <GLES3/gl3.h>
#include "../utils.h"
#include "../shader.h"

#include <iostream>

using namespace std;

class ColorTriangle {
    private:
    
    union UniformValue {
        int intVal;
    };

    public:

    enum class Uniform : uint32_t {
        Color = 0
    };

    struct UniformData {
        Uniform type;
        UniformValue val;
    };

    struct UniformDataIntType {
        int type;
        UniformValue val;
    };

    void init();

    void set();

    void setUniform(UniformDataIntType data);

    void setUniform(const UniformData data);

    void render();

    private:

    const float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    GLuint program;

    Uniform mapUniform(int val);

    struct {
        GLfloat color[3];
    }tmp;
};