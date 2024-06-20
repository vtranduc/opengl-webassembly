#pragma once

#include <GLES3/gl3.h>
#include "../../math.h"
#include <iostream>

class Sphere {
public:
    Sphere();

    ~Sphere();

    void generateVertices(int nTheta = 50, int nPhi = 50);

    GLfloat* getVertices() const;

    GLsizeiptr getSize() const;

    GLsizei getCount() const;

private:
    float r = 0.5f;

    struct {
        GLfloat *vertices = nullptr;

        GLsizeiptr size = 0;

        GLsizei count = 0;
    }mesh;
};