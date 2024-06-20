#pragma once

#include <GLES3/gl3.h>
#include "../shader.h"
#include "../utils.h"
#include "../math.h"
#include "presetBase.h"

#include <iostream>

using namespace std;

class SpheresAndLights final : public PresetBase {
public:
    SpheresAndLights();

    void init() override;

    void set() override;

    void command(const CommandData& data) override;

    void render() override;

    struct Callbacks {

    };

    void setCallbacks(const Callbacks& callbacks);

private:
    GLuint program;

    World world;

    View view;

    Projection projection;

    Sphere sphere0;
};