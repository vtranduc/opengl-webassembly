#include "../../../headers/math/matrix/matrix.h"

Matrix::Matrix() : Matrix(4) {};

Matrix::Matrix(int squareDim) : Matrix(squareDim, squareDim) {};

Matrix::Matrix(const int numCols, int numRows) {
    assert(numCols > 0 && numRows > 0 && numCols <= 512 && numRows <= 512);
    nCols = numCols; nRows = numRows;
    elements = new float*[nCols];
    for (int i = 0; i < nCols; i++) elements[i] = new float[nRows];
};

Matrix::~Matrix() {
    for (int i = 0; i < nCols; i++) delete[] elements[i];
    delete[] elements;
}

Matrix& Matrix::zero() { for (int i = 0; i < nCols; i++) for (int j = 0; j < nRows; j++) elements[i][j] = 0.0f; return *this; };

Matrix& Matrix::identity() {
    for (int i = 0; i < nCols; i++) for (int j = 0; j < nRows; j++) elements[i][j] = static_cast<float>(i == j);
    return *this;
};

int Matrix::sizeCols() const { return nCols; };

int Matrix::sizeRows() const { return nRows; };

void Matrix::display(ostream& os) const {
    for (int i = 0; i < sizeRows(); i++) {
        for (int j = 0; j < sizeCols(); j++) os << elements[j][i] << ", " ;
        os << "\n";
    }
};

float* Matrix::operator[](int iCol) { return elements[iCol]; };

Matrix Matrix::operator*( Matrix& multiplier) {
    assert(sizeCols() == multiplier.sizeRows());
    Matrix result(multiplier.sizeCols(), sizeRows());
    result.zero();
    for (int i = 0; i < result.sizeRows(); i++) {
        for (int j = 0; j < result.sizeCols(); j++) {
            for (int k = 0; k < sizeCols(); k++) result[j][i] += (*this)[k][i] * multiplier[j][k];
        }
    }
    return result;
};

ostream& operator<<(ostream& os, const Matrix& matrix) { matrix.display(os); return os; };
