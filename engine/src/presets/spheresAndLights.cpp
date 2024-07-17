#include "../../headers/presets/spheresAndLights.h"

SpheresAndLights::SpheresAndLights() {}

void SpheresAndLights::init() {
    program = getShaderProgram(Shader::Vertex::SpheresAndLights, Shader::Fragment::SpheresAndLights);
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection.value());
    float position[3] = { 1.0f, 1.0f, 1.0f };
    float target[3] = { 0.0f, 0.0f, 0.0f };
    view.setPosition(position);
    view.lookAt(target);

    highlightProgram = getShaderProgram(Shader::Vertex::Extrude, Shader::Fragment::Mono);
    glUseProgram(highlightProgram);
    glUniformMatrix4fv(glGetUniformLocation(highlightProgram, "projection"), 1, GL_FALSE, projection.value());
    glUniform1f(glGetUniformLocation(highlightProgram, "uDistance"), 0.05f);
    glUniform3f(glGetUniformLocation(highlightProgram, "uColor"), 1.0f, 0.0f, 1.0f);

    grid = new Grid(&projection, &view);

    for (int i = 0; i < 3; i++) {
        Geometry* geometry;
        switch (i) {
        case 0:
            geometry = new Sphere(0.5f);
            geometry->setPosition(0.0f, 0.0f, 0.0f);
            break;
        case 1:
            geometry = new Sphere(0.25f);
            geometry->setPosition(0.75f, 0.0f, 0.0f);
            break;
        case 2:
            geometry = new RectangularCuboid();
            geometry->setPosition(-1.0f, 0.0f, 0.0f);
            break;
        default: throw "Unaccounted geometry";
        }

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

        GLuint colorBuffer;
        glGenBuffers(1, &colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, geometry->getSize(), geometry->getColors(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,            // attribute. No particular reason for 1, but must match the layout in the shader.
            3,            // size
            GL_FLOAT,     // type
            GL_TRUE,     // normalized?
            0,            // stride
            (void*)0      // array buffer offset
        );

        objects.push_back({ VBO, VAO, normalBuffer, colorBuffer, geometry });
    }

    inversionProgram = getShaderProgram(Shader::Vertex::BasicPP, Shader::Fragment::InvertPP);
    glUseProgram(inversionProgram);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &framebuffers.quadVAO);
    glGenBuffers(1, &framebuffers.quadVBO);
    glBindVertexArray(framebuffers.quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, framebuffers.quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glGenFramebuffers(1, &framebuffers.framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffers.framebuffer);    

    glGenTextures(1, &framebuffers.textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, framebuffers.textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffers.textureColorbuffer, 0); 

    // Render buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800);  

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) throw "Frame buffer failed\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SpheresAndLights::set() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    setDirty();
}

void SpheresAndLights::cleanUp() {
    glCullFace(GL_BACK);
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

    case SpheresAndLightsCommand::Type::ToggleSelection:
        iSelected = (iSelected + 1) % objects.size();
        setDirty();
        break;

    case SpheresAndLightsCommand::Type::RotateObjectRight:
        objects[iSelected].geometry->rotateTheta(-0.1f);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::RotateObjectLeft:
        objects[iSelected].geometry->rotateTheta(0.1f);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::RotateObjectUp:
        objects[iSelected].geometry->rotatePhi(-0.1f);
        setDirty();
        break;
    case SpheresAndLightsCommand::Type::RotateObjectDown:
        objects[iSelected].geometry->rotatePhi(0.1f);
        setDirty();
        break;

    case SpheresAndLightsCommand::Type::TogglePostProcessing:
        postProcessingEnabled = !postProcessingEnabled;
        setDirty();
        break;

    default:
        break;
    }
}

void SpheresAndLights::render() {
    PresetBase::render();

    if (postProcessingEnabled) glBindFramebuffer(GL_FRAMEBUFFER, framebuffers.framebuffer);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view.value());

    for (auto object : objects) drawObject(program, object);

    glDisable(GL_CULL_FACE);
    grid->draw();
    glEnable(GL_CULL_FACE);

    glUseProgram(highlightProgram);
    glCullFace(GL_FRONT);
    glUniformMatrix4fv(glGetUniformLocation(highlightProgram, "view"), 1, GL_FALSE, view.value());
    drawObject(highlightProgram, objects[iSelected]);
    glCullFace(GL_BACK);
    
    if (postProcessingEnabled) {
        glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(inversionProgram);
        glBindVertexArray(framebuffers.quadVAO);
        glBindTexture(GL_TEXTURE_2D, framebuffers.textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_DEPTH_TEST);
    }
}

void SpheresAndLights::drawObject(GLuint program, GeometryAndBuffers object) {
    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, object.normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, object.colorBuffer);
    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, object.geometry->getWorldValue());
    glDrawArrays(GL_TRIANGLES, 0, object.geometry->getCount());
}

void SpheresAndLights::setCallbacks(const Callbacks& callbacks) {}