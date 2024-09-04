#pragma once

#include "../object3D.h"

class Light : public Object3D {

public:

    Light() = default;

private:

    float intensity = 1.0f;
};