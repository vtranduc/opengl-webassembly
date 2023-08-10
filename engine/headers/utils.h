#pragma once

#include "utils/shader.h"

struct RGB { double r; double g; double b; };

RGB hexToRGB(int hex);

float* asColorArray(RGB rgb, float* array);