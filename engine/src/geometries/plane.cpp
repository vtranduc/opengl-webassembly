#include "../../headers/geometries/plane.h"

Plane::Plane() : Geometry(2) {
    const GLfloat vertices[18] = {
        -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        
        -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f
    };
    for (int i = 0; i < 18; i++) setVertexValue(vertices[i], i);
};