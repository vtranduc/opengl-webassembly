#include "../headers/webglHandle.h"

int WebGLHandle::initialize(char* canvasId, int clearColor) {
    setContextAttribute();
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context
        = emscripten_webgl_create_context(canvasId, &attrs);
    if (context < 0) {
        printf("failed to create webgl context %d\n", context);
        return 0;
    };
    EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(context);
    if (r < 0) {
        printf("failed to make webgl current %d\n", r);
        return 0;
    }
    int purple = 0xff00ff;
    RGB rgb = hexToRGB(clearColor);
    glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    return 1;
};

int WebGLHandle::setClearColor(int hex) {
    RGB rgb = hexToRGB(hex);
    glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    return 1;
}

void WebGLHandle::setContextAttribute() {
    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;
};