#pragma once

#include "material.h"

class Cel : public Material {

public:

    Cel();

private:

    UniformData colorUniform{ "uColor", UniformData::Color, { .integer = 0xffff00 } };
};