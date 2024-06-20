#pragma once

#include <GLES3/gl3.h>
#include "../../math.h"
#include <iostream>

class Sphere {
public:
    Sphere();

    ~Sphere();

    void generateVertices(int nTheta = 64, int nPhi = 64);

    GLfloat* getVertices() const;

    GLfloat* getNormals() const;

    GLsizeiptr getSize() const;

    GLsizei getCount() const;

private:
    float r = 0.5f;

    struct {
        GLfloat *vertices = nullptr;

        GLfloat *normals = nullptr;

        GLsizeiptr size = 0;

        GLsizei count = 0;
    }mesh;
};