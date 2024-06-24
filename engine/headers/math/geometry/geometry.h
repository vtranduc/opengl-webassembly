#pragma once

#include <GLES3/gl3.h>
#include "../matrix/world.h"
#include <iostream>

using namespace std;

class Geometry {

public:

    Geometry();

    GLfloat* getVertices() const;

    GLfloat* getNormals() const;

    GLsizeiptr getSize() const;

    GLsizei getCount() const;

    const float* getWorldValue();

    void setPosition(float x, float y, float z);

protected:

    struct {
        GLfloat *vertices = nullptr;

        GLfloat *normals = nullptr;

        GLsizeiptr size = 0;

        GLsizei count = 0;
    }mesh;

private:

    World world;
};