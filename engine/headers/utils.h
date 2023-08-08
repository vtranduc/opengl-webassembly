#pragma once

// #include <iostream>
// #include <GLES3/gl3.h>
#include "utils/shader.h"

// using namespace std;

struct RGB { double r; double g; double b; };

RGB hexToRGB(int hex);

// class Utils {
//     public:

//     class Shader {
//         public:

//         static GLuint get(const GLchar* source, GLenum type);

//         static GLuint getProgram(GLuint vertexShader, GLuint fragmentShader, bool deleteShader = true);
//     };
// };