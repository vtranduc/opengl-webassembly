#pragma once

#include <iostream>
#include <GLES3/gl3.h>
#include "../shader.h"
#include "../shaderSource.h"

using namespace std;

GLuint getShader(Shader::Vertex shader);

GLuint getShader(Shader::Fragment shader);

GLuint getShader(const GLchar* source, GLenum type);

GLuint getShaderProgram(Shader::Vertex vertex, Shader::Fragment fragment);

GLuint getShaderProgram(GLuint vertexShader, GLuint fragmentShader, bool deleteShader = true);
