#pragma once

#include <math.h>
#include "gl.h"
#include "../vector/vector3.h"

class View : public GLMatrix {

public:

    void lookAt(const float* target);

    void lookAt(float x, float y, float z);

    void setPosition(const float* position);

    void setPosition(float x, float y, float z);

    Vector3& getPosition(Vector3* out) const;

    Vector3& getTarget(Vector3* out) const;

    void rotateThetaInYUpConvention(float theta);

    void rotatePhiInYUpConvention(float phi);

private:

    Vector3
        position{ 0.0f },
        target{ 0.0f, 0.0f, -1.0f },
        front{ 0.0f, 0.0f, -1.0f },
        right{ 1.0f, 0.0f, 0.0f },
        up{ 0.0f, 1.0f, 0.0f },
        tmp, tmp_;

    bool validatePositionTarget(const Vector3& position, const Vector3& target);

    void updateMatrix() override;
};