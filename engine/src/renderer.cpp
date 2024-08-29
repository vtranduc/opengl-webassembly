#include "../headers/renderer.h"

Renderer::Renderer(Camera* camera_) { camera = camera_; };

Renderer::MeshBufferData Renderer::processMesh(Mesh& mesh) {
    MeshBufferData data;
    data.mesh = &mesh;
    auto meshData = mesh.getRenderData();
    data.externalUniforms = meshData.material.requiredExternalUniforms;
    data.count = meshData.geometry.count;
    data.program = getShaderProgram(meshData.material.shader.vertex, meshData.material.shader.fragment);

    processBuffer(&data.vertexBuffer, meshData.geometry.size, meshData.geometry.vertices);
    processVertexArrayObject(&data.vertexArray);
    processVertexAttribute(0, 3 * sizeof(float));

    processBuffer(&data.normalBuffer, meshData.geometry.size, meshData.geometry.normals);
    processVertexAttribute(1);

    return data;
}

Renderer::LightBufferData::Point Renderer::processLight(PointLight& light) {
    return Renderer::LightBufferData::Point{};
}

Renderer::LightBufferData::Directional Renderer::processLight(DirectionalLight& light) {
    return Renderer::LightBufferData::Directional{};
}

void Renderer::renderMesh(const MeshBufferData& data) {
    glUseProgram(data.program);
    glBindBuffer(GL_ARRAY_BUFFER, data.vertexBuffer);
    glBindVertexArray(data.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, data.normalBuffer);
    for (auto uniform : data.externalUniforms) {
        switch (uniform)
        {
        case Material::RenderData::ExternalUniforms::Projection:
            glUniformMatrix4fv(glGetUniformLocation(data.program, "projection"), 1, GL_FALSE, camera->getProjectionValue());
            break;
        case Material::RenderData::ExternalUniforms::View:
            glUniformMatrix4fv(glGetUniformLocation(data.program, "view"), 1, GL_FALSE, camera->getViewValue());
            break;
        case Material::RenderData::ExternalUniforms::World:
            glUniformMatrix4fv(glGetUniformLocation(data.program, "world"), 1, GL_FALSE, data.mesh->getWorldValue());
            break;
        default:
            break;
        }
    }
    for (auto uniform : data.mesh->getUniforms()) {
        switch (uniform->type) {
        case Material::UniformData::Type::Color:
            glUniform3f(
                glGetUniformLocation(data.program, uniform->name),
                float(uniform->data.integer >> 16) / 255.f,
                float((uniform->data.integer >> 8) & 255) / 255.f,
                float(uniform->data.integer & 255) / 255.f
            );
            break;
        default:
            break;
        }
    }
    glDrawArrays(GL_TRIANGLES, 0, data.count);
};

void Renderer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Renderer::processBuffer(GLuint* buffer, GLsizeiptr size, const GLfloat* data) {
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
};

void Renderer::processVertexArrayObject(GLuint* VAO) {
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}

void Renderer::processVertexAttribute(GLuint index, GLsizei stride) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
        index,            // attribute. No particular reason for 1, but must match the layout in the shader.
        3,            // size
        GL_FLOAT,     // type
        GL_TRUE,     // normalized?
        stride,            // stride
        (void*)0      // array buffer offset
    );
}
