#include <iostream>
#include <emscripten.h>
#include "headers/webglHandle.h"

using namespace std;

static WebGLHandle handle;

extern "C" const char* sayHello(char* name, int repeat) {
    string str;
    for (int i = 0; i <= repeat; i++) str += "Hello, " + (string)name + "!\n";
    const char* ptr = str.c_str();
    return ptr;
}

extern "C" int initialize(char* canvasId, int clearColor) {
    // return handle.initialize(canvasId, clearColor);

    return handle.test3(canvasId);
}

extern "C" int render() {
    // return handle.render();

    return 0;
}

extern "C" int setClearColor(int color) {
    return handle.setClearColor(color);
}

int main() {
    cout << "Hello World" << endl;
    return 1;
}