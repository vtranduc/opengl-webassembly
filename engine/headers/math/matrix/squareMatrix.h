#pragma once

#include <math.h>
#include "matrix.h"

class SquareMatrix : public Matrix {

public:

    SquareMatrix(int dimension);

    ~SquareMatrix();

    int size() const;

    SquareMatrix operator*(const SquareMatrix& multiplier);

    SquareMatrix& multiply(const SquareMatrix& multiplier);

    float determinant() const;

private:

    int dim;

    float* elementArr;

    static float determinantOut(float** elements, unsigned int size);

    static float determinantOut(float** elements, unsigned int size, float* out);

    static float** minorOut(float** elements, unsigned int size, unsigned int col, unsigned int row, float** out);

    // Now inaccessible methods from base class

    using Matrix::operator*;

    using Matrix::multiply;
};