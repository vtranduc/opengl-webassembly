#include "../../../headers/math/matrix/world.h"

void World::updateMatrix() {
    for (int i = 0; i < 3; i++) e(3, i) = position[i];
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) e(i, j) = scale[j] * rotationMx[i][j];
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
