#pragma once

#include "material.h"

class SphereMirror : public Material {

public:

    SphereMirror();

private:

    UniformData colorUniform{ "uColor", UniformData::Color, { .integer = 0xffff00 } };
};