#pragma once

#include <GLES3/gl3.h>
#include <iostream>

using namespace std;

class Geometry {

public:

    Geometry() = delete;

    Geometry(int nTriangles);

    ~Geometry();

    GLfloat* getVertices() const;

    GLfloat* getNormals() const;

    GLsizeiptr getSize() const;

    GLsizei getCount() const;

    struct RenderData {

        GLsizeiptr size;

        GLsizei count;

        GLfloat* vertices;

        GLfloat* normals;
    };

    RenderData getRenderData() const;

protected:

    GLfloat getVertexValue(int index) const;

    void setVertexValue(GLfloat value, int index);

    void setNormalValue(GLfloat value, int index);

private:

    GLfloat *vertices = nullptr, *normals = nullptr;

    GLsizeiptr size;

    GLsizei count;
};