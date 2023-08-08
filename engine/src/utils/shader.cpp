#include "../../headers/utils/shader.h"

GLuint getShader(Shader::Vertex shader) {
    return getShader(getShaderSource(shader), GL_VERTEX_SHADER);
};

GLuint getShader(Shader::Fragment shader) {
    return getShader(getShaderSource(shader), GL_FRAGMENT_SHADER);
};

GLuint getShader(const GLchar* source, GLenum type) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    GLint  success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "Shader has failed to compiled: " << infoLog << endl;
    }

    return shader;
};

GLuint getShaderProgram(Shader::Vertex vertex, Shader::Fragment fragment) {
    return getShaderProgram(getShader(vertex), getShader(fragment));
};

GLuint getShaderProgram(GLuint vertexShader, GLuint fragmentShader, bool deleteShader) {
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint  success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Program has failed to link: " << infoLog << endl;
    }

    if (deleteShader) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    return program;
};