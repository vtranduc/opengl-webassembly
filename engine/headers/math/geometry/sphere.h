#pragma once

#include <GLES3/gl3.h>
#include "../../math.h"
#include <iostream>
#include "geometry.h"

class Sphere : public Geometry {
public:
    Sphere(float radius = 1.0f);

    ~Sphere();

    void generateVertices(int nTheta = 64, int nPhi = 64);


private:
    float r = 0.5f;
};