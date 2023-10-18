#pragma once

#include <iostream>
#include <functional>
#include <cassert>
#include "../../compileSettings.h"

using namespace std;

class Matrix {

public:

    Matrix();

    Matrix(int squareDim);

    Matrix(int nCols, int nRows);

    ~Matrix();

    Matrix& zero();

    Matrix& identity();

    int sizeCols() const;

    int sizeRows() const;

    int sizeElements() const;

    float* value() const;

    void display(ostream& os) const;

    float** operator[](int iCol) const;

    Matrix operator*(const Matrix& multiplier);

    Matrix& multiply(const Matrix& multiplier);

    Matrix& multiply(float scalar);

    Matrix& transpose();

    Matrix& copy(const float* arr);

    Matrix& copy(float** elements);

    Matrix& copy(const Matrix& mx);

protected:

    float* elementArr;

    float*** elements;

    float* multiplyOut(const Matrix& mx1, const Matrix& mx2, float* out);

    Matrix& multiplyOut(const Matrix& mx1, const Matrix& mx2, Matrix* out);

    void doElements(const function<void(float*, int, int)> callback);

    void doElements(const function<void(float*, int, int)> callback) const;

private:

    int nCols, nRows, nElements;

    void allocateElements(const int numCols, const int numRows);

    void freeElements();
};

ostream& operator<<(ostream& leftOperand, const Matrix& rightOperand);