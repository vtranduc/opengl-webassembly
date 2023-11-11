#pragma once

#include <iostream>
#include <GLES3/gl3.h>
#include "presetBase.h"

using namespace std;

class StaticGLTF : public PresetBase {

public:

    void init() override;

    void set() override;

    void command(const CommandData& data) override;

    void render() override;

    struct Callbacks {};

    void setCallbacks(const Callbacks& callbacks);

private:

    Callbacks callbacks;
};