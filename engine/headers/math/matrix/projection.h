#pragma once

#include <math.h>
#include "gl.h"
#include "../../compileSettings.h"

class Projection : public GLMatrix {

public:

    Projection();

    enum class Mode {
        Orthographic,
        Perspective
    };

    void setMode(Mode mode);

    void setPerspectiveSpecs(float fovY, float aspect, float near, float far);

    void setOrthographicSpecs(float right, float left, float top, float bottom, float near, float far);

private:

    Mode mode = Mode::Perspective;

    void updateMatrix() override;

    void applyPerspective();

    void applyOrthographic();

    struct {
        float fovY = M_PI / 2.0f;
        float aspect = 1.0f;
        float near = 0.02f;
        float far = 100.0f;
    }perspectiveSpecs;

    struct {
        float right = 1.0f;
        float left = -1.0f;
        float top = 1.0f;
        float bottom = -1.0f;
        float near = 0.0f;
        float far = 100.0f;
    }orthographicSpecs;
};