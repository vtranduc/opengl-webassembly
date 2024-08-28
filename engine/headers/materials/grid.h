#pragma once

#include "material.h"

class GridMaterial : public Material {

public:

    GridMaterial();

private:

    struct {
        UniformData origin{ "uColorOrigin", UniformData::Color, { .integer = 0xc0c0c0 }};

        UniformData major{ "uColorMajor", UniformData::Color, { .integer = 0x808080 }};

        UniformData minor{ "uColorMinor", UniformData::Color, { .integer = 0xa0a0a0 }};

        UniformData x{ "uColorX", UniformData::Color, { .integer = 0xff0000 }};

        UniformData z{ "uColorZ", UniformData::Color, { .integer = 0x0000ff }};
    }colors;
};