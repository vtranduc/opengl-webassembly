#include "../../headers/presets/spheresAndLights.h"

SpheresAndLights::SpheresAndLights() {}

void SpheresAndLights::init() {
    program = getShaderProgram(Shader::Vertex::VertexColor, Shader::Fragment::VertexColor);
    float position[3] = { 1.0f, 1.0f, 1.0f };
    float target[3] = { 0.0f, 0.0f, 0.0f };
    view.setPosition(position);
    view.lookAt(target);
}

void SpheresAndLights::set() {
    glUseProgram(program);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphere0.getSize(), sphere0.getVertices(), GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, world.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());

    setDirty();
}

void SpheresAndLights::command(const CommandData& data) {}

void SpheresAndLights::render() {
    PresetBase::render();
    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, world.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, sphere0.getCount());
}

void SpheresAndLights::setCallbacks(const Callbacks& callbacks) {}