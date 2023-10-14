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
    float** tmpElements;
    switch (size) {
        case 0: throw "Matrix cannot be empty!";
        case 1: *out += elements[0][0]; return *out;
        case 2: *out += elements[0][0] * elements[1][1] - elements[1][0] * elements[0][1]; return *out;
        case 3:
            tmpElements = new float*[2]; tmpElements[0] = new float[2]; tmpElements[1] = new float[2]; 
            for (int i = 0; i < 3; i++) *out += pow(-1.0f, i) * elements[i][0] * determinantOut(minorOut(elements, 3, i, 0, tmpElements), 2);
            delete[] tmpElements[0]; delete[] tmpElements[1]; delete[] tmpElements;
            return *out;
        default: break;
    }

    for (int i = 0; i < size; i++) {
        float** subElements = new float*[size - 1];
        for (int j = 0; j < size - 1; j++) subElements[j] = new float[size - 1];
        // Do your logics

        
        
        // ------------------------
        for (int j = 0; j < size - 1; j++) delete[] subElements[j];
        delete[] subElements;
    }
    return *out;
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