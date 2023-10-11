#include "../../../headers/math/matrix/squareMatrix.h"

SquareMatrix::SquareMatrix(int dimension) : Matrix(dimension) { dim = dimension; };

int SquareMatrix::size() const { return dim; };