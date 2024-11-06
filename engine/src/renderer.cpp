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

Renderer::PostEffectBufferData Renderer::processPostEffect(PostEffect& postEffect) {
    PostEffectBufferData data;
    auto postEffectData = postEffect.getRenderData();
    data.program = getShaderProgram(postEffectData.shader.vertex, postEffectData.shader.fragment);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &data.quadVAO);
    glGenBuffers(1, &data.quadVBO);
    glBindVertexArray(data.quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, data.quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glGenFramebuffers(1, &data.frame);
    glBindFramebuffer(GL_FRAMEBUFFER, data.frame);    

    glGenTextures(1, &data.textureColor);
    glBindTexture(GL_TEXTURE_2D, data.textureColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.width, windowSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data.textureColor, 0); 

    // Render buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, windowSize.width, windowSize.height);  

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw "Frame buffer failed\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return data;
};

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





void Renderer::preprocessPostEffect(const PostEffectBufferData& data) {
    glBindFramebuffer(GL_FRAMEBUFFER, data.frame);
}

void Renderer::processPostEffect(const PostEffectBufferData& data) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(data.program);
    glBindVertexArray(data.quadVAO);
    glBindTexture(GL_TEXTURE_2D, data.textureColor);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}



















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
