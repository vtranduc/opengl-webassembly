#include "../../../headers/math/matrix/gl.h"

GLMatrix::GLMatrix() {
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

GLMatrix::~GLMatrix() {
    for (int i = 0; i < 4; i++) delete[] elements[i];
    delete[] elements;
};

const float* GLMatrix::value() {
    if (!isDirty) return elementArr;
    updateMatrix();
    isDirty = false;
    return elementArr;
};

float& GLMatrix::e(int col, int row) { return *elements[col][row]; };

void GLMatrix::setDirty() { isDirty = true; };