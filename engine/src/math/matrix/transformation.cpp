#include "../../../headers/math/matrix/transformation.h"

Transformation::Transformation() {
    // Allocate elements
    elements = new float**[4];
    int iArr = 0;
    for (int i = 0; i < 4; i++) {
        elements[i] = new float*[4];
        for (int j = 0; j < 4; j++) elements[i][j] = &elementArr[iArr++];
    }
    // Set identity
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) *elements[i][j] = static_cast<float>(i == j);
};

Transformation::~Transformation() {
    for (int i = 0; i < 4; i++) delete[] elements[i];
    delete[] elements;
};

const float* Transformation::value() const { return elementArr; };

void Transformation::translateInPlace(const float* xyz) { translateInPlace(xyz[0], xyz[1], xyz[2]); };

void Transformation::translateInPlace(float x, float y, float z) {
    position.add(x, y, z);
    isDirty = true;
};

void Transformation::scaleInPlace(const float* xyz) { scaleInPlace(xyz[0], xyz[1], xyz[2]); };

void Transformation::scaleInPlace(float x, float y, float z) {
    scale.multiply(x, y, z);
    isDirty = true;
};

Transformation::RotationMatrix::RotationMatrix() {
    // Allocate elements
    elements = new float*[3];
    for (int i = 0; i < 3; i++) elements[i] = new float[3];
    // Identity
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) elements[i][j] = static_cast<float>(i == j);
};

Transformation::RotationMatrix::~RotationMatrix() {
    for (int i = 0; i < 3; i++) delete[] elements[i];
    delete[] elements;
};

float* Transformation::RotationMatrix::operator[](int i) const { return elements[i]; };

const float* Transformation::updateMatrix() {
    if (!isDirty) return value();
    for (int i = 0; i < 3; i++) *elements[3][i] = position[i];
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) *elements[i][j] = scale[j] * rotationMx[i][j];
    isDirty = false;
    return value();
};