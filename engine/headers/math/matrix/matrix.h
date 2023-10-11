#pragma once

#include <iostream>
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

    void display(ostream& os) const;

    float* operator[](int iCol);

    Matrix operator*( Matrix& multiplier);

private:

    int nCols, nRows;

    float** elements;
};

ostream& operator<<(ostream& leftOperand, const Matrix& rightOperand);