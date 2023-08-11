#pragma once

#include <GLES3/gl3.h>

struct RGB { double r; double g; double b; };

RGB hexToRGB(int hex);

GLfloat* asColorArray(RGB rgb, GLfloat* array);