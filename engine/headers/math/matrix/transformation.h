#pragma once

#include "matrix4.h"

class TransformationMatrix : public Matrix4 {

public:

    TransformationMatrix();

    TransformationMatrix& translate(float x, float y, float z);

    TransformationMatrix& translate(float* coord);

    TransformationMatrix& scale(float scalar);

    TransformationMatrix& scale(float x, float y, float z);

    TransformationMatrix& scale(float* scaleXYZ);
};