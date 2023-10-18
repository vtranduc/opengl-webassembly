#pragma once

#include <math.h>
#include "matrix.h"

class SquareMatrix : public Matrix {

public:

    SquareMatrix(int dimension);

    int size() const;

    SquareMatrix operator*(const SquareMatrix& multiplier);

    SquareMatrix& multiply(const SquareMatrix& multiplier);

    SquareMatrix& invert();

    float determinant() const;

private:

    int dim;

    float tmpElementArr[16];

    static float determinantOut(float* elements, unsigned int size);

    static float determinantOut(float* elements, unsigned int size, float* out);

    float* cofactorOut(float* out) const;

    static float* minorOut(float* elements, unsigned int size, unsigned int col, unsigned int row, float* out);

    using Matrix::operator*;

    using Matrix::multiply;
};