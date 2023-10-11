#pragma once

#include <iostream>
#include <functional>
#include <cassert>

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

    void display(ostream& os) const;

    float* operator[](int iCol) const;

    Matrix operator*(const Matrix& multiplier);

    Matrix& multiply(const Matrix& multiplier);

protected:

    float* multiplyOut(const Matrix& mx1, const Matrix& mx2, float* out);

    Matrix& multiplyOut(const Matrix& mx1, const Matrix& mx2, Matrix* out);

private:

    int nCols, nRows;

    float** elements;

    void allocateElements(const int numCols, const int numRows);

    void freeElements();

    Matrix& copy(const float* arr);

    void doElements(const function<void(float*, int, int)> callback);
};

ostream& operator<<(ostream& leftOperand, const Matrix& rightOperand);