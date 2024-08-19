#pragma once

#include "math.h"

class Object3D {

public:

    Object3D() = default;

    const float* getWorldValue();

private:

    World world;
};