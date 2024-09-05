#pragma once

#include <GLES3/gl3.h>
#include <vector>
#include "../shader.h"
#include "../utils.h"
#include "../math.h"
#include "presetBase.h"
#include "../object3D/grid.h"
#include "../renderer.h"
#include "../scene.h"
#include "../mesh.h"
#include "../postEffect.h"
#include <iostream>

using namespace std;

class ThreeBabylonConcept : public PresetBase {

public:
    ThreeBabylonConcept() = default;

    void init() override;

    void set() override;

    virtual void cleanUp() override;

    void command(const CommandData& data) override;

    void render() override;

private:

    Scene scene;
};