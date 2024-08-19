#pragma once

#include "geometry.h"
#include "../math.h"

class Sphere : public Geometry {

public:

    Sphere();

    Sphere(float radius, int nTheta, int nPhi);

private:

    float radius;

    void generateVertices(int nTheta, int nPhi);

    int getNumOfTriangles(int nTheta, int nPhi);
};