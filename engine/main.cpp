#include <iostream>
#include <emscripten.h>
#include "headers/webglHandle.h"
#include "headers/preset.h"
#include "headers/presets/uniform.h"

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

extern "C" int setColorTriangleColor(int color) {
    return handle.command(
        {
            .colorTriangle =
                {
                    .type = ColorTriangleCommand::Color,
                    .value= { .intVal = color }
                }
        }
    );
}

extern "C" int usePreset(int presetCode) { return handle.usePreset(presetCode); };

extern "C" int onClearColorChange(void(*f)(int color)) {
    handle.webCallbacks.onClearColorChange = f;
    return 1;
}
