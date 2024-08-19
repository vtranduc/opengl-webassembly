#pragma once

#include <algorithm>

using namespace std;

class Color {

public:

    Color() = delete;

    Color(float everyComponent = 0.8f);

    void set(float everyComponent);

    void set(float r, float g, float b);

private:

    float r, g, b;

    float correct(float value);
};