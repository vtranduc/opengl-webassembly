#include "../../../headers/math/matrix/projection.h"

Projection::Projection() : GLMatrix() { setDirty(); };

void Projection::setMode(Mode mode_) {
    if (mode == mode_) return;
    mode = mode_;
    setDirty();
}

void Projection::setPerspectiveSpecs(float fovY, float aspect, float near, float far) {
    #if ASSERT_VALID_ARGUMENTS
    assert(fovY < M_PI && aspect > 0.0 && far > near);
    #endif
    perspectiveSpecs.fovY = fovY;
    perspectiveSpecs.aspect = aspect;
    perspectiveSpecs.near = near;
    perspectiveSpecs.far = far;
    if (mode == Mode::Perspective) setDirty();
};

void Projection::setOrthographicSpecs(float right, float left, float top, float bottom, float near, float far) {
    #if ASSERT_VALID_ARGUMENTS
    assert(right > left && top > bottom && near > far);
    #endif
    orthographicSpecs.right = right;
    orthographicSpecs.left = left;
    orthographicSpecs.top = top;
    orthographicSpecs.bottom = bottom;
    orthographicSpecs.near = near;
    orthographicSpecs.far = far;
    if (mode == Mode::Orthographic) setDirty();
};

void Projection::updateMatrix() {
    switch (mode) {
        case Mode::Perspective: applyPerspective(); break;
        case Mode::Orthographic: applyOrthographic(); break;
        default: throw "Invalid mode";
    }
}

void Projection::applyPerspective() {
    float d = 1.0f / tan(perspectiveSpecs.fovY / 2.0f);
    float nearMinusFar = perspectiveSpecs.near - perspectiveSpecs.far;
    e(0, 0) = d / perspectiveSpecs.aspect;
    e(1, 1) = d;
    e(2, 2) = (perspectiveSpecs.far + perspectiveSpecs.near) / nearMinusFar;
    e(2, 3) = -1.0f;
    e(3, 0) = 0.0f;
    e(3, 1) = 0.0f;
    e(3, 2) = (2.0f * perspectiveSpecs.far * perspectiveSpecs.near) / nearMinusFar;
    e(3, 3) = 0.0f;
}

void Projection::applyOrthographic() {
    e(0, 0) = 2.0f / (orthographicSpecs.right - orthographicSpecs.left);
    e(1, 1) = 2.0f / (orthographicSpecs.top - orthographicSpecs.bottom);
    e(2, 2) = -2.0f / (orthographicSpecs.far - orthographicSpecs.near);
    e(2, 3) = 0.0f;
    e(3, 0) = (orthographicSpecs.right + orthographicSpecs.left)
        / (orthographicSpecs.left - orthographicSpecs.right);
    e(3, 1) = (orthographicSpecs.top + orthographicSpecs.bottom)
        / (orthographicSpecs.bottom - orthographicSpecs.top);
    e(3, 2) = (orthographicSpecs.far + orthographicSpecs.near)
        / (orthographicSpecs.near - orthographicSpecs.far);
    e(3, 3) = 1.0f;
}