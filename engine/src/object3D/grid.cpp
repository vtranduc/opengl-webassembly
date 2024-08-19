#include "../../headers/object3D/grid.h"

Grid::Grid(Projection* projection_, View* view_) {
    projection = projection_;
    view = view_;

    glUseProgram(program);

    glUniformMatrix4fv(glGetUniformLocation(program, "world"), 1, GL_FALSE, getWorldValue());
    glUniform3f(glGetUniformLocation(program, "uColorX"), 1.0f, 0.0f, 0.0f);
    glUniform3f(glGetUniformLocation(program, "uColorZ"), 0.0f, 0.0f, 1.0f);
    glUniform3f(glGetUniformLocation(program, "uColorMinor"), 0.55f, 0.55f, 0.55f);
    glUniform3f(glGetUniformLocation(program, "uColorMajor"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(program, "uColorOrigin"), 0.4f, 0.4f, 0.4f);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Grid::draw() {
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, projection->value());
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, view->value());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}