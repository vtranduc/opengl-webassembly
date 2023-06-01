#include "../headers/utils.h"

RGB hexToRGB(int hex) {
    double r = double((hex >> 16) & 0xFF) / 255.0;
    double g = double((hex >> 8) & 0xFF) / 255.0;
    double b = double((hex) & 0xFF) / 255.0;
    return RGB { r, g, b };
}