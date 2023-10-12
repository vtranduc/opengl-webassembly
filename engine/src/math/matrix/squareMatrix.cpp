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