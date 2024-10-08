#include "../../../headers/math/matrix/view.h"

constexpr struct {
    float lookAtMinDistance = 0.01;

    float maxFrontDotY = 0.99;

    float minPhiInYUpConvention = 0.01;
}tolerance;

void View::updateMatrix() {
    front.copy(target).subtract(position).normalize();
    right.copy(front).crossY().normalize();
    Vector3::cross(right, front, &up);
    for (int i = 0; i < 3; i++) {
        e(i, 0) = right[i];
        e(i, 1) = up[i];
        e(i, 2) = -front[i];
    };
    e(3, 0) = -Vector3::dot(right, position);
    e(3, 1) = -Vector3::dot(up, position);
    e(3, 2) = Vector3::dot(front, position);
};

void View::lookAt(const float* target) { lookAt(target[0], target[1], target[2]); };

void View::lookAt(float x, float y, float z) {
    if (!validatePositionTarget(position, tmp_.set(x, y, z))) return;
    target.set(x, y, z);
    setDirty();
};

void View::setPosition(const float* position) { setPosition(position[0], position[1], position[2]); };

void View::setPosition(float x, float y, float z) {
    if (!validatePositionTarget(tmp_.set(x, y, z), target)) return;
    position.set(x, y, z);
    setDirty();
};

bool View::validatePositionTarget(const Vector3& position, const Vector3& target) {
    tmp.copy(position).subtract(target);
    if (tmp.length() < tolerance.lookAtMinDistance) return false;
    if (abs(tmp.normalize().y) > tolerance.maxFrontDotY) return false;
    return true;
};

Vector3& View::getPosition(Vector3* out) const { out->copy(position); return *out; };

Vector3& View::getTarget(Vector3* out) const { out->copy(target); return *out; };

void View::rotateThetaInYUpConvention(float theta) {
    position.subtract(target).cartesianToSphericalYUpConvention().addY(theta)
        .sphericalToCartesianYUpConvention().add(target);
    setDirty();
}

void View::rotatePhiInYUpConvention(float phi) {
    tmp.copy(position).subtract(target).cartesianToSphericalYUpConvention().addZ(phi);
    if (tmp.z < tolerance.minPhiInYUpConvention || tmp.z > M_PI - tolerance.minPhiInYUpConvention) return;
    position.copy(tmp).sphericalToCartesianYUpConvention().add(target);
    setDirty();
}