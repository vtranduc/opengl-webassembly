#include "../headers/color.h"

Color::Color(float everyComponent) { set(everyComponent); }

void Color::set(float everyComponent) { r = g = b = correct(everyComponent); };

void Color::set(float r_, float g_, float b_) { r = correct(r_); g = correct(g_); b = correct(b_); };

float Color::correct(float value) { return clamp(value, 0.0f, 1.0f); }