#pragma once

#include <GLES3/gl3.h>
#include "math/matrix/view.h"
#include "camera.h"
#include "mesh.h"
#include <iostream>

using namespace std;

class Renderer {

public:
    Renderer() = delete;

    Renderer(Camera* camera);

    struct MeshBufferData {
        GLint program;

        GLuint vertexBuffer;

        GLuint vertexArray;

        GLuint normalBuffer;

        Mesh* mesh;

        vector<Material::RenderData::ExternalUniforms> externalUniforms;

        GLsizei count;
    };

    MeshBufferData processMesh(Mesh& mesh);

    void renderMesh(const MeshBufferData& data);

    void clear();

private:

    Camera* camera = nullptr;

    void processBuffer(GLuint* VBO, GLsizeiptr size, const GLfloat* data);

    void processVertexArrayObject(GLuint* VAO);

    void processVertexAttribute(GLuint index, GLsizei stride = 0);
};