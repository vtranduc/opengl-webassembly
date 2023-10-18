#include "../../../headers/math/matrix/squareMatrix.h"

SquareMatrix::SquareMatrix(int dimension) : Matrix(dimension) { dim = dimension; };

int SquareMatrix::size() const { return dim; };

SquareMatrix SquareMatrix::operator*(const SquareMatrix& multiplier) {
    assert(size() == multiplier.size());
    multiplyOut(*this, multiplier, tmpElementArr);
    SquareMatrix out(size());
    out.copy(tmpElementArr);
    return out;
};

SquareMatrix& SquareMatrix::multiply(const SquareMatrix& multiplier) {
    assert(size() == multiplier.size());
    multiplyOut(*this, multiplier, tmpElementArr);
    this->copy(tmpElementArr);
    return *this;
};

SquareMatrix& SquareMatrix::invert() {
    switch(size()) {
        case 0: throw "Matrix cannot be empty!";
        case 1: elementArr[0] = 1.0f / elementArr[0]; return *this;
        default: break;
    }
    const float det = determinant();
    float* tmpElements;
    tmpElements = new float[size() * size()];
    cofactorOut(tmpElements);
    copy(tmpElements);
    transpose();
    multiply(1.0f / det);
    delete[] tmpElements;
    return *this;
};

float SquareMatrix::determinant() const {
    float out = 0;
    determinantOut(elementArr, size(), &out);
    return out;
}

float SquareMatrix::determinantOut(float* elements, unsigned int size) {
    float tmp = 0;
    return determinantOut(elements, size, &tmp);
};

float SquareMatrix::determinantOut(float* elements, unsigned int size, float* out) {
    switch (size) {
        case 0: throw "Matrix cannot be empty!";
        case 1: *out += elements[0]; return *out;
        case 2:
            *out += elements[0] * elements[3] - elements[2] * elements[1];
            return *out;
        default: break;
    }
    unsigned int minorSize = size - 1;
    float* tmpElements;
    tmpElements = new float[minorSize * minorSize];
    for (int i = 0; i < size; i++) *out += pow(-1.0f, i) * elements[i * size] * determinantOut(minorOut(elements, size, i, 0, tmpElements), minorSize);
    delete[] tmpElements;
    return *out;
};

float* SquareMatrix::cofactorOut(float* out) const {
    unsigned int minorSize = size() - 1;
    float* tmpElements;
    tmpElements = new float[minorSize * minorSize];
    int iArr = 0;
    doElements([&](float* e, int i, int j)->void
        { out[iArr++] = pow(-1.0f, i + j) * determinantOut(minorOut(elementArr, this->size(), i, j, tmpElements), minorSize); });
    delete[] tmpElements;
    return out;
};

float* SquareMatrix::minorOut(float* elements, unsigned int size, unsigned int col, unsigned int row, float* out) {
    int iArr = 0;
    for (int i = 0; i < size * size; i++) if ((i / size) != col && (i % size) != row) out[iArr++] = elements[i];
    return out;
};