#pragma once

#include <GLES3/gl3.h>
#include "math/matrix/view.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"
#include "postEffect.h"
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

    struct LightBufferData {
        struct Point {};

        struct Directional {};
    };

    struct PostEffectBufferData {
        GLuint program, frame, quadVAO, quadVBO, textureColor;
    };

    MeshBufferData processMesh(Mesh& mesh);

    LightBufferData::Point processLight(PointLight& light);

    LightBufferData::Directional processLight(DirectionalLight& light);

    PostEffectBufferData processPostEffect(PostEffect& postEffect);

    void renderMesh(const MeshBufferData& data);

    void preprocessPostEffect(const PostEffectBufferData& data);

    void processPostEffect(const PostEffectBufferData& data);

    void clear();

private:

    Camera* camera = nullptr;

    struct {
        int width = 800;
        
        int height = 800;
    }windowSize;

    void processBuffer(GLuint* VBO, GLsizeiptr size, const GLfloat* data);

    void processVertexArrayObject(GLuint* VAO);

    void processVertexAttribute(GLuint index, GLsizei stride = 0);
};