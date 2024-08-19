#pragma once

#include <iostream>
#include "geometry.h"
#include "../vector.h"

using namespace std;

class RectangularCuboid_ : public Geometry_ {

public:

    RectangularCuboid_();

    ~RectangularCuboid_();

    void generateVertices();

private:

    Vector3 v0, v1, v2;
};