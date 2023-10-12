#pragma once

#include "matrix.h"

class SquareMatrix : public Matrix {

public:

    SquareMatrix(int dimension);

    ~SquareMatrix();

    int size() const;

    SquareMatrix operator*(const SquareMatrix& multiplier);

    SquareMatrix& multiply(const SquareMatrix& multiplier);

private:

    int dim;

    float* elementArr;

    // Now inaccessible methods from base class

    using Matrix::operator*;

    using Matrix::multiply;
};