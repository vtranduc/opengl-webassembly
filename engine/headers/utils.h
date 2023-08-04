#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

struct RGB { double r; double g; double b; };

RGB hexToRGB(int hex);

static unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile shader!" << endl;
        cout << message << endl;
    }

    return id;
}

static unsigned int createShader(const string& vertexShaderSource, const string& fragmentShaderSource) {
    //
    unsigned int program = glCreateProgram();
    // unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    // unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // glAttachShader(program, vs);
    // glAttachShader(program, fs);

    // glLinkProgram(program);
    // glValidateProgram(program);

    // glDeleteShader(vs);
    // glDeleteShader(fs);

    // ----------------------

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const char* a = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &a, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* b = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &b, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        // glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // ...
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // 0. copy our vertices array in a buffer for OpenGL to use

    // ----------------------

    // return program;

    
}