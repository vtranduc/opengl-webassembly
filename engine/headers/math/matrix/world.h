#pragma once

#include "gl.h"
#include "../vector/vector3.h"

class World : public GLMatrix {

public:

    void setPosition(float x, float y, float z);

    void translateInPlace(const float* xyz);

    void translateInPlace(float x, float y, float z);

    void scaleInPlace(const float* xyz);

    void scaleInPlace(float x, float y, float z);

    Vector3& getPosition(Vector3* out) const;

    Vector3& getScale(Vector3* out) const;

private:

    Vector3 position{ 0.0f }, scale{ 1.0f };

    void updateMatrix() override;

    class RotationMatrix {

    public:

        RotationMatrix();

        ~RotationMatrix();

        float* operator[](int i) const;

    private:

        float** elements;

    }rotationMx;
};