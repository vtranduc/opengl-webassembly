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
}

void ColorTriangle::setUniform(UniformDataIntType data) {
    setUniform(UniformData { mapUniform(data.type), data.val });
}

void  ColorTriangle::setUniform(const UniformData data) {
    switch (data.type) {
        case Uniform::Color:
            glUniform3fv(
                glGetUniformLocation(program, "uColor"),
                1,
                asColorArray(hexToRGB(data.val.intVal), tmp.color)
            );
            break;
        default: throw "Uniform type is not handled";
    }
}

void ColorTriangle::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

ColorTriangle::Uniform ColorTriangle::mapUniform(int val) {
    return static_cast<Uniform>(val);
}
