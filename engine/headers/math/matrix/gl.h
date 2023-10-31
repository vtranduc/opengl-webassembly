#pragma once

#include <iostream>

using namespace std;

class GLMatrix {

public:

    GLMatrix();

    ~GLMatrix();

    const float* value();

private:

    float elementArr[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    float*** elements;

    bool isDirty = false;

    virtual void updateMatrix()=0;

protected:

    float& e(int col, int row);

    void setDirty();

    void display();
};