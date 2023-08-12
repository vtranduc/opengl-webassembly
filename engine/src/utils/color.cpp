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

int asHex(GLfloat* array) {
    return (((int)(round(array[0] * 255.)) & 0xff) << 16)
        + (((int)(round(array[1] * 255.f)) & 0xff) << 8)
        + ((int)(round(array[2] * 255.f)) & 0xff);
}