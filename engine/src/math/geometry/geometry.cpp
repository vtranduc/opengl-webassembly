#include "../../../headers/math/geometry/geometry.h"

Geometry::Geometry() {}

GLfloat* Geometry::getVertices() const { return mesh.vertices; }

GLfloat* Geometry::getNormals() const { return mesh.normals; }

GLfloat* Geometry::getColors() const { return mesh.colors; }

GLsizeiptr Geometry::getSize() const { return mesh.size; }

GLsizei Geometry::getCount() const { return mesh.count; }

const float* getWorldValue();

const float* Geometry::getWorldValue() { return world.value(); }

void Geometry::setPosition(float x, float y, float z) { world.setPosition(x, y, z); };