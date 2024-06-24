#include "../../headers/presets/spheresAndLights.h"

SpheresAndLights::SpheresAndLights() {}

void SpheresAndLights::init() {
    program = getShaderProgram(Shader::Vertex::SpheresAndLights, Shader::Fragment::SpheresAndLights);
    float position[3] = { 1.0f, 1.0f, 1.0f };
    float target[3] = { 0.0f, 0.0f, 0.0f };
    view.setPosition(position);
    view.lookAt(target);

    geometries.push_back(new Sphere(0.5f));
    geometries.push_back(new Sphere(0.25f));
    geometries.push_back(new RectangularCuboid());
    geometries[0]->setPosition(0.0f, 0.0f, 0.0f);
    geometries[1]->setPosition(0.75f, 0.0f, 0.0f);
    geometries[2]->setPosition(-1.0f, 0.0f, 0.0f);
}

void SpheresAndLights::set() {
    glUseProgram(program);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    setDirty();
}

void SpheresAndLights::command(const CommandData& data) {
    switch (data.spheresAndLights.type) {
    case SpheresAndLightsCommand::Type::CameraRight:
        view.rotateThetaInYUpConvention(0.1);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::CameraLeft:
        view.rotateThetaInYUpConvention(-0.1);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::CameraUp:
        view.rotatePhiInYUpConvention(-0.1);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::CameraDown:
        view.rotatePhiInYUpConvention(0.1);
        setDirty();
        break;
    default:
        break;
    }
}

void SpheresAndLights::render() {
    PresetBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());

    for (auto geometry : geometries) {
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, geometry->getSize(), geometry->getVertices(), GL_STATIC_DRAW);

        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        GLuint normalBuffer;
        glGenBuffers(1, &normalBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
        glBufferData(GL_ARRAY_BUFFER, geometry->getSize(), geometry->getNormals(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,            // attribute. No particular reason for 1, but must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_TRUE,     // normalized?
            0,            // stride
            (void*)0      // array buffer offset
        );

        glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, geometry->getWorldValue());

        glDrawArrays(GL_TRIANGLES, 0, geometry->getCount());
    }
}

void SpheresAndLights::setCallbacks(const Callbacks& callbacks) {}