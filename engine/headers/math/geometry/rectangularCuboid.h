#pragma once

#include <iostream>
#include "geometry.h"
#include "../vector.h"

using namespace std;

class RectangularCuboid : public Geometry {

public:

    RectangularCuboid();

    ~RectangularCuboid();

    void generateVertices();

private:

    Vector3 v0, v1, v2;
};