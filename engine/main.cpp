#include <iostream>
#include <emscripten.h>
#include "headers/webglHandle.h"
#include "headers/preset.h"

using namespace std;

static WebGLHandle handle;

extern "C" const char* sayHello(char* name, int repeat) {
    string str;
    for (int i = 0; i <= repeat; i++) str += "Hello, " + (string)name + "!\n";
    const char* ptr = str.c_str();
    return ptr;
}

extern "C" int initialize(char* canvasId, int clearColor) {
    return handle.initialize(canvasId, clearColor);
}

extern "C" int setClearColor(int color) {
    return handle.setClearColor(color);
}

extern "C" int setUniform(int type, int value) {
    Preset::UniformData data;
    data.colorTriangle.type = type;
    data.colorTriangle.val.intVal = value;
    return handle.setUniform(data);
}

// int main() {
//     cout << "Hello World" << endl;
//     return 1;
// }