#include "../../../headers/math/geometry/rectangularCuboid.h"

RectangularCuboid_::RectangularCuboid_() { generateVertices(); };

RectangularCuboid_::~RectangularCuboid_() { delete[] mesh.vertices; delete[] mesh.normals; delete[] mesh.colors;}

void RectangularCuboid_::generateVertices() {
    const int nTriangles = 12;
    mesh.size = nTriangles * 9 * sizeof(GLfloat);
    mesh.count = nTriangles * 3;
    const GLfloat vertices[nTriangles * 9] = {
        -0.5,-0.5,-0.5, // triangle 1 : begin
        -0.5,-0.5, 0.5,
        -0.5, 0.5, 0.5, // triangle 1 : end
        0.5, 0.5,-0.5, // triangle 2 : begin
        -0.5,-0.5,-0.5,
        -0.5, 0.5,-0.5, // triangle 2 : end
        0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        0.5,-0.5, 0.5,
        -0.5,-0.5, 0.5,
        -0.5,-0.5,-0.5,
        -0.5, 0.5, 0.5,
        -0.5,-0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5,-0.5,
        0.5,-0.5,-0.5,
        0.5, 0.5, 0.5,
        0.5,-0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5,-0.5,
        -0.5, 0.5,-0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5,-0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        0.5,-0.5, 0.5
    };
    mesh.vertices = new float[nTriangles * 9];
    for (int i = 0; i < nTriangles * 9; i++) mesh.vertices[i] = vertices[i];
    mesh.normals = new float[nTriangles * 9];
    for (int i = 0; i < nTriangles; i++) {
        int index = i * 9;
        for (int j = 0; j < 3; j++) {
            v0[j] = vertices[index + j];
            v1[j] = vertices[index + 3 + j];
            v2[j] = vertices[index + 6 + j];
        }
        v1.subtract(v0).cross(v2.subtract(v0)).normalize();
        for (int j = 0; j < 3; j++) {
            mesh.normals[index + j] = v1[j];
            mesh.normals[index + 3 + j] = v1[j];
            mesh.normals[index + 6 + j] = v1[j];
        }
    }

    mesh.colors = new float[nTriangles * 9];

    for (int i = 0; i < nTriangles * 9; i++) mesh.colors[i] = 0.8; 
}
