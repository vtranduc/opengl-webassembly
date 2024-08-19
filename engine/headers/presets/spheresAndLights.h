#pragma once

#include <GLES3/gl3.h>
#include <vector>
#include "../shader.h"
#include "../utils.h"
#include "../math.h"
#include "presetBase.h"
#include "../object3D/grid.h"

#include <iostream>

using namespace std;

class SpheresAndLights final : public PresetBase {
public:
    SpheresAndLights();

    void init() override;

    void set() override;

    virtual void cleanUp() override;

    void command(const CommandData& data) override;

    void render() override;

    struct Callbacks {

    };

    void setCallbacks(const Callbacks& callbacks);

private:
    GLuint program, highlightProgram, inversionProgram;

    View view;

    Projection projection;

    struct GeometryAndBuffers{
        GLuint VBO;

        GLuint VAO;

        GLuint normalBuffer;

        GLuint colorBuffer;

        Geometry_* geometry;
    };

    struct {
        GLuint framebuffer, quadVAO, quadVBO, textureColorbuffer;
    }framebuffers;

    vector<GeometryAndBuffers> objects;

    int iSelected = 0;

    void drawObject(GLuint program, GeometryAndBuffers object);

    Grid *grid;

    bool postProcessingEnabled = false;
};