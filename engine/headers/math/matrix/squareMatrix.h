#pragma once

#include "matrix.h"

class SquareMatrix : public Matrix {

public:

    SquareMatrix(int dimension);

    int size() const;

private:

    int dim;
};