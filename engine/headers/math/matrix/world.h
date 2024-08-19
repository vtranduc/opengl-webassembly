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

    void rotateTheta(float delta);

    void rotatePhi(float delta);

private:

    Vector3 position{ 0.0f }, scale{ 1.0f };

    void updateMatrix() override;

    class RotationMatrix {

    public:

        RotationMatrix();

        ~RotationMatrix();

        float* operator[](int i) const;

        void rotateTheta(float delta);

        void rotatePhi(float delta);

        void update();

    private:

        float** elements;

        float theta = 0.0f, phi = M_HALFPI;

        bool isDirty = false;

        Vector3 front, back, right, up;
        
    }rotationMx;
};