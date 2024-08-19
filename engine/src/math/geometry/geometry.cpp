#include "../../../headers/math/geometry/geometry.h"

Geometry_::Geometry_() {}

GLfloat* Geometry_::getVertices() const { return mesh.vertices; }

GLfloat* Geometry_::getNormals() const { return mesh.normals; }

GLfloat* Geometry_::getColors() const { return mesh.colors; }

GLsizeiptr Geometry_::getSize() const { return mesh.size; }

GLsizei Geometry_::getCount() const { return mesh.count; }

const float* Geometry_::getWorldValue() { return world.value(); }

void Geometry_::setPosition(float x, float y, float z) { world.setPosition(x, y, z); };

void Geometry_::rotateTheta(float delta) { world.rotateTheta(delta); };

void Geometry_::rotatePhi(float delta) { world.rotatePhi(delta); };