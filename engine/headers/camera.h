#pragma once

#include "math.h"

class Camera {

public:

    Camera() = default;

    const GLfloat* getProjectionValue();

    const GLfloat* getViewValue();

    void setPosition(const float* position);

    void lookAt(const float* target);

private:

    View view;

    Projection projection;
};