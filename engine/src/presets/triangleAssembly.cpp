#include "../../headers/presets/triangleAssembly.h"

void TriangleAssembly::init() {
    program = getShaderProgram(Shader::Vertex::Basic, Shader::Fragment::Mono);
}

void TriangleAssembly::set() {
    glUseProgram(program);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    setDirty();
}

void TriangleAssembly::command(const CommandData& data) {};

void TriangleAssembly::render() {
    PresetBase::render();

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, nTriangles * 3);
}
