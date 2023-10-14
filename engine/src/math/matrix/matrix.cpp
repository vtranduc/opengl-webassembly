#include "../../../headers/math/matrix/matrix.h"

Matrix::Matrix() : Matrix(4) {};

Matrix::Matrix(int squareDim) : Matrix(squareDim, squareDim) {};

Matrix::Matrix(const int numCols, const int numRows) {
    assert(numCols > 0 && numRows > 0 && numCols <= 512 && numRows <= 512);
    allocateElements(numCols, numRows);
};

Matrix::~Matrix() { freeElements(); }

Matrix& Matrix::zero() { doElements(([&](float* e, int, int)->void { *e = 0.0f; })); return *this; };

Matrix& Matrix::identity() {
    doElements(([&](float* e, int i, int j)->void { *e = static_cast<float>(i == j); }));
    return *this;
};

int Matrix::sizeCols() const { return nCols; };

int Matrix::sizeRows() const { return nRows; };

int Matrix::sizeElements() const { return nCols * nRows; };

void Matrix::display(ostream& os) const {
    for (int i = 0; i < sizeRows(); i++) {
        for (int j = 0; j < sizeCols(); j++) os << elements[j][i] << ", " ;
        os << "\n";
    }
};

float* Matrix::operator[](int iCol) const { return elements[iCol]; };

Matrix Matrix::operator*(const Matrix& multiplier) {
    assert(sizeCols() == multiplier.sizeRows());
    Matrix result(multiplier.sizeCols(), sizeRows());
    multiplyOut(*this, multiplier, &result);
    return result;
};

Matrix& Matrix::multiply(const Matrix& multiplier) {
    assert(sizeCols() == multiplier.sizeRows());
    float* elementArr = new float[multiplier.sizeCols() * sizeRows()];
    multiplyOut(*this, multiplier, elementArr);
    freeElements();
    allocateElements(multiplier.sizeCols(), sizeRows());
    this->copy(elementArr);
    delete[] elementArr;
    return *this;
};

Matrix& Matrix::multiply(float scalar) {
    doElements([&](float* e, int i, int j)->void { *e = *e * scalar; });
    return *this;
};

Matrix& Matrix::transpose() {
    float** tmpElements;
    tmpElements = new float*[nRows];
    for (int i = 0; i < nRows; i++) tmpElements[i] = new float[nCols];
    doElements([&](float* e, int i, int j)->void { tmpElements[j][i] = *e; });
    freeElements();
    allocateElements(nRows, nCols);
    copy(tmpElements);
    for (int i = 0; i < nCols; i++) delete[] tmpElements[i]; delete[] tmpElements;
    return *this;
}

Matrix& Matrix::copy(const float* arr) {
    int iArr = 0;
    doElements([&](float* e, int i, int j)->void { *e = arr[iArr++]; });
    return *this;
}

Matrix& Matrix::copy(float** elements) {
    doElements([&](float* e, int i, int j)->void { *e = elements[i][j]; });
    return *this;
};

Matrix& Matrix::copy(const Matrix& mx) {
    assert(sizeCols() == mx.sizeCols() && sizeRows() == mx.sizeRows());
    doElements([&](float* e, int i, int j)->void { *e = mx[i][j]; });
    return *this;
};

float* Matrix::multiplyOut(const Matrix& mx1, const Matrix& mx2, float* out) {
    int iArr = 0;
    for (int i = 0; i < mx2.sizeCols(); i++) {
        for (int j = 0; j < mx1.sizeRows(); j++) {
            out[iArr] = 0.0f;
            for (int k = 0; k < mx1.sizeCols(); k++) out[iArr] += mx1[k][j] * mx2[i][k];
            iArr++;
        }
    }
    return out;
};

Matrix& Matrix::multiplyOut(const Matrix& mx1, const Matrix& mx2, Matrix* out) {
    float* elementArr = new float[out->sizeElements()];
    multiplyOut(mx1, mx2, elementArr);
    out->copy(elementArr);
    delete[] elementArr;
    return *out;
};

void Matrix::doElements(const function<void(float*, int, int)> callback) {
    for (int i = 0; i < nCols; i++) for (int j = 0; j < nRows; j++) callback(&((*this)[i][j]), i, j);
};

void Matrix::doElements(const function<void(float*, int, int)> callback) const {
    for (int i = 0; i < nCols; i++) for (int j = 0; j < nRows; j++) callback(&((*this)[i][j]), i, j);
};

void Matrix::allocateElements(const int numCols, const int numRows) {
    nCols = numCols; nRows = numRows;
    elements = new float*[nCols];
    for (int i = 0; i < nCols; i++) elements[i] = new float[nRows];
};

void Matrix::freeElements() {
    for (int i = 0; i < nCols; i++) delete[] elements[i];
    delete[] elements;
}

ostream& operator<<(ostream& os, const Matrix& matrix) { matrix.display(os); return os; };
