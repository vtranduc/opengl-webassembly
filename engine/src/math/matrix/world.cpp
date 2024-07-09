#include "../../../headers/math/matrix/world.h"

constexpr struct {
    struct {
        float min = 0.01;
        float max = M_PI - 0.01;
    }phi;
}tolerance;

void World::updateMatrix() {
    rotationMx.update();
    for (int i = 0; i < 3; i++) e(3, i) = position[i];
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) e(i, j) = scale[j] * rotationMx[i][j];
};

void World::setPosition(float x, float y, float z) {
    position.set(x, y, z);
    setDirty();
};

void World::translateInPlace(const float* xyz) { translateInPlace(xyz[0], xyz[1], xyz[2]); };

void World::translateInPlace(float x, float y, float z) {
    position.add(x, y, z);
    setDirty();
};

void World::scaleInPlace(const float* xyz) { scaleInPlace(xyz[0], xyz[1], xyz[2]); };

void World::scaleInPlace(float x, float y, float z) {
    scale.multiply(x, y, z);
    setDirty();
};

Vector3& World::getPosition(Vector3* out) const { out->copy(position); return *out; };

Vector3& World::getScale(Vector3* out) const { out->copy(scale); return *out; };

void World::rotateTheta(float delta) { rotationMx.rotateTheta(delta); setDirty(); };

void World::rotatePhi(float delta) { rotationMx.rotatePhi(delta); setDirty(); };

World::RotationMatrix::RotationMatrix() {
    // Allocate elements
    elements = new float*[3];
    for (int i = 0; i < 3; i++) elements[i] = new float[3];
    // Identity
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) elements[i][j] = static_cast<float>(i == j);
};

World::RotationMatrix::~RotationMatrix() {
    for (int i = 0; i < 3; i++) delete[] elements[i];
    delete[] elements;
};

float* World::RotationMatrix::operator[](int i) const { return elements[i]; };


void World::RotationMatrix::rotateTheta(float delta) {
    theta = fmodf(theta + fmodf(delta, M_2PI) + M_2PI, M_2PI);
    isDirty = true;
};

void World::RotationMatrix::rotatePhi(float delta) {
    phi = min(tolerance.phi.max, max(tolerance.phi.min, phi + delta));
    isDirty = true;
};

void World::RotationMatrix::update() {
    if (!isDirty) return;
    isDirty = false;
    Vector3::sphericalToCartesianYUpConvention(1.0f, theta, phi, &back);
    front.copy(back).multiply(-1.0f);
    right.copy(front).crossY().normalize();
    Vector3::cross(right, front, &up);
    for (int i = 0; i < 3; i++) {
        elements[i][0] = right[i];
        elements[i][1] = up[i];
        elements[i][2] = back[i];
    };
}