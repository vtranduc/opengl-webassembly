#include "../../headers/geometries/geometry.h"

Geometry::Geometry(int nTriangles) {
    vertices = new float[nTriangles * 9];
    normals = new float[nTriangles * 9];
    size = nTriangles * 9 * sizeof(GLfloat);
    count = nTriangles * 3;
}

Geometry::~Geometry() { delete[] vertices; delete[] normals; }

GLfloat* Geometry::getVertices() const { return vertices; };

GLfloat* Geometry::getNormals() const { return normals; };

GLsizeiptr Geometry::getSize() const { return  size; };

GLsizei Geometry::getCount() const { return  count; };

Geometry::RenderData Geometry::getRenderData() const {
    return { getSize(), getCount(), getVertices(), getNormals() };
}

GLfloat Geometry::getVertexValue(int index) const { return vertices[index]; };

void Geometry::setVertexValue(GLfloat value, int index) { vertices[index] = value; };

void Geometry::setNormalValue(GLfloat value, int index) { normals[index] = value; };
