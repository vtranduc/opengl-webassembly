#include "../../headers/utils.h"

RGB hexToRGB(int hex) {
    double r = double((hex >> 16) & 0xFF) / 255.0;
    double g = double((hex >> 8) & 0xFF) / 255.0;
    double b = double((hex) & 0xFF) / 255.0;
    return { r, g, b};
}

GLfloat* asColorArray(RGB rgb, GLfloat* array) {
    array[0] = rgb.r;
    array[1] = rgb.g;
    array[2] = rgb.b;
    return array;
}