#pragma once

#include "matrix4.h"
#include "../vector/vector3.h"

class Transformation {

public:

    Transformation();

    ~Transformation();

    const float* value() const;

    const float* updateMatrix();

    void translateInPlace(const float* xyz);

    void translateInPlace(float x, float y, float z);

private:

    bool isDirty = false;

    float elementArr[16];
    
    float*** elements;

    Vector3 position{ 0.0f }, scale{ 1.0f };

    class RotationMatrix {

    public:

        RotationMatrix();

        ~RotationMatrix();

        float* operator[](int i) const;

    private:

        float** elements;

    }rotationMx;
};