#include "../../headers/presets/triangleAssembly.h"

void TriangleAssembly::init() {
    program = getShaderProgram(Shader::Vertex::VertexColor, Shader::Fragment::VertexColor);
}

void TriangleAssembly::set() {
    glUseProgram(program);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(
        1,            // attribute. No particular reason for 1, but must match the layout in the shader.
        3,            // size
        GL_FLOAT,     // type
        GL_FALSE,     // normalized?
        0,            // stride
        (void*)0      // array buffer offset
    );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, world.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());
    setDirty();
};

void TriangleAssembly::command(const CommandData& data) {
    switch (data.triangleAssembly.type) {
    case TriangleAssemblyCommand::Type::Color: break;
    case TriangleAssemblyCommand::Type::Translate:
        world.translateInPlace(data.triangleAssembly.value.float3);
        setDirty();
        break;
    case TriangleAssemblyCommand::Type::Scale:
        world.scaleInPlace(data.triangleAssembly.value.float3);
        setDirty();
        break;
    case TriangleAssemblyCommand::Type::PositionCamera:
        view.setPosition(data.triangleAssembly.value.float3);
        setDirty();
        break;
    case TriangleAssemblyCommand::Type::LookAt:
        view.lookAt(data.triangleAssembly.value.float3);
        setDirty();
        break;
    default:
        throw "Unhandled case";
    }
};

void TriangleAssembly::render() {
    PresetBase::render();
    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, world.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, nTriangles * 3);
};
