#include "../../headers/presets/colorTriangle.h"

void ColorTriangle::init() {
    program = getShaderProgram(Shader::Vertex::Basic, Shader::Fragment::Mono);
}

void ColorTriangle::set() {
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

void ColorTriangle::command(const CommandData& data) {
    switch(data.colorTriangle.type) {
        case ColorTriangleCommand::Type::Color:
            glUniform3fv(
                glGetUniformLocation(program, "uColor"),
                1,
                asColorArray(hexToRGB(data.colorTriangle.value.intVal), tmp.color)
            );
            setDirty();
            onColorUpdated();
            break;
        default:
            throw "Unhandled case";
    }
};

void ColorTriangle::render() {
    PresetBase::render();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ColorTriangle::setCallbacks(const Callbacks& cbs) {
    callbacks.onColorUpdated = cbs.onColorUpdated;
}

void ColorTriangle::onColorUpdated() {
    glGetUniformfv(program, 1, tmp.color);
    callbacks.onColorUpdated(asHex(tmp.color));
}