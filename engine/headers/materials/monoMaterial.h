#pragma once

#include "material.h"

class MonoMaterial : public Material {

public:

    MonoMaterial();

private:

    UniformData colorUniform{ "uColor", UniformData::Color, { .integer = 0xff00ff } };
};