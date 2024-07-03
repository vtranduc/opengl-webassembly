#pragma once

#include "object3D.h"
#include "../shader.h"
#include "../utils.h"
#include "../math.h"

class Grid : public Object3D {

public:

    Grid(Projection* projection, View* view);

    void draw();

private:

    const GLuint program = getShaderProgram(Shader::Vertex::VaryingWorldPosition, Shader::Fragment::Grid);

    const GLfloat vertices[18] = {
        -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        
        -1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f
    };

    Projection *projection;

    View *view;
};