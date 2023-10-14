#include "../../../headers/math/matrix/squareMatrix.h"

SquareMatrix::SquareMatrix(int dimension) : Matrix(dimension) {
    dim = dimension;
    elementArr = new float[dim * dim];
};

SquareMatrix::~SquareMatrix() { delete[] elementArr; };

int SquareMatrix::size() const { return dim; };

SquareMatrix SquareMatrix::operator*(const SquareMatrix& multiplier) {
    assert(size() == multiplier.size());
    multiplyOut(*this, multiplier, elementArr);
    SquareMatrix out(size());
    out.copy(elementArr);
    return out;
};

SquareMatrix& SquareMatrix::multiply(const SquareMatrix& multiplier) {
    assert(size() == multiplier.size());
    multiplyOut(*this, multiplier, elementArr);
    this->copy(elementArr);
    return *this;
};

SquareMatrix& SquareMatrix::invert() {
    switch(size()) {
        case 0: throw "Matrix cannot be empty!";
        case 1: elements[0][0] = 1.0f / elements[0][0]; return *this;
        default: break;
    }
    const float det = determinant();
    float** tmpElements;
    tmpElements = new float*[size()];
    for (int i = 0; i < size(); i++) tmpElements[i] = new float[size()];
    cofactorOut(tmpElements);
    copy(tmpElements);
    transpose();
    multiply(1.0f / det);
    for (int i = 0; i < size(); i++) delete[] tmpElements[i]; delete[] tmpElements;
    return *this;
};

float SquareMatrix::determinant() const {
    float out = 0;
    determinantOut(elements, size(), &out);

    return out;
}

float SquareMatrix::determinantOut(float** elements, unsigned int size) {
    float tmp = 0;
    return determinantOut(elements, size, &tmp);
};

float SquareMatrix::determinantOut(float** elements, unsigned int size, float* out) {
    switch (size) {
        case 0: throw "Matrix cannot be empty!";
        case 1: *out += elements[0][0]; return *out;
        case 2: *out += elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1]; return *out;
        default: break;
    }
    unsigned int minorSize = size - 1;
    float** tmpElements;
    tmpElements = new float*[minorSize];
    for (int i = 0; i < minorSize; i++) tmpElements[i] = new float[minorSize];
    for (int i = 0; i < size; i++) *out += pow(-1.0f, i) * elements[i][0] * determinantOut(minorOut(elements, size, i, 0, tmpElements), minorSize);
    for (int i = 0; i < minorSize; i++) delete[] tmpElements[i]; delete[] tmpElements;
    return *out;
}

float** SquareMatrix::cofactorOut(float** out) const {
    unsigned int minorSize = size() - 1;
    float** tmpElements;
    tmpElements = new float*[minorSize];
    for (int i = 0; i < minorSize; i++) tmpElements[i] = new float[minorSize];
    doElements([&](float* e, int i, int j)->void
        { out[i][j] = pow(-1.0f, i + j) * determinantOut(minorOut(elements, this->size(), i, j, tmpElements), minorSize); });

    for (int i = 0; i < minorSize; i++) delete[] tmpElements[i]; delete[] tmpElements;
    return out;
}

float** SquareMatrix::minorOut(float** elements, unsigned int size, unsigned int col, unsigned int row, float** out) {
    unsigned int iCol = 0, iRow;
    for (int i = 0; i < size; i++) {
        if (i == col) continue;
        iRow = 0;
        for (int j = 0; j < size; j++) {
            if (j == row) continue;
            out[iCol][iRow] = elements[i][j];
            iRow++;
        }
        iCol++;
    }
    return out;
}