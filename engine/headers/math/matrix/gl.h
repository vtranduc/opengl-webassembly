#pragma once

class GLMatrix {

public:

    GLMatrix();

    ~GLMatrix();

    const float* value();

private:

    float elementArr[16];

    float*** elements;

    bool isDirty = false;

    virtual void updateMatrix()=0;

protected:

    float& e(int col, int row);

    void setDirty();
};