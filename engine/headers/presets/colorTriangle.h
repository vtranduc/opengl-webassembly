#pragma once

#include <GLES3/gl3.h>
#include "presetBase.h"
#include "../utils.h"
#include "../shader.h"
#include "uniform.h"
#include <functional>
#include "../utils/callback.h"

#include <iostream>

using namespace std;

class ColorTriangle : public PresetBase {
    public:

    struct Callbacks {
        CallbackVI onColorUpdated;
    };

    void init() override;

    void set() override;

    void cleanUp() override;

    void command(const CommandData& data) override;

    void render() override;

    void setCallbacks(const Callbacks& callbacks);

    private:

    Callbacks callbacks;

    const float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    GLuint program;

    struct {
        GLfloat color[3];
    }tmp;

    void onColorUpdated();
};