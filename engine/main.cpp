#include <iostream>
#include <emscripten.h>
#include "headers/webglHandle.h"
#include "headers/preset.h"
#include "headers/presets/uniform.h"
#include "headers/utils/callback.h"

using namespace std;

static WebGLHandle handle;

extern "C" const char* sayHello(char* name, int repeat) {
    string str;
    for (int i = 0; i <= repeat; i++) str += "Hello, " + (string)name + "!\n";
    const char* ptr = str.c_str();
    return ptr;
}

extern "C" int initialize(char* canvasId, int clearColor, int startingPreset) {
    return handle.initialize(canvasId, clearColor, startingPreset);
}

extern "C" int setClearColor(int color) {
    return handle.setClearColor(color);
}

extern "C" int usePreset(int presetCode) { return handle.usePreset(presetCode); };

extern "C" int onClearColorChange(void(*f)(int color)) {
    handle.webCallbacks.onClearColorChange = f;
    return 1;
}

extern "C" int setColorTriangleColor(int color) {
    return handle.command
    (
        {
            Preset::Name::ColorTriangle,
            {
                .colorTriangle =
                {
                    .type = ColorTriangleCommand::Color,
                    .value= { .intVal = color }
                }
            }
        }
    );
}

extern "C" int onColorTriangleUpdated(CallbackVI onColorUpdated2) {
    handle.setPresetCallbacks({ Preset::Name::ColorTriangle, { .colorTriangle={onColorUpdated2} } });
    return 1;
}

extern "C" int translateTriangleAssembly(float x, float y, float z) {
    return handle.command
    (
        {
            Preset::Name::TriangleAssembly,
            {
                .triangleAssembly = {
                    .type = TriangleAssemblyCommand::Type::Translate,
                    .value =
                    {
                        .float3 = { x, y, z }
                    }
                }
            }
        }
    );
};

extern "C" int scaleTriangleAssembly(float x, float y, float z) {
    return handle.command
    (
        {
            Preset::Name::TriangleAssembly,
            {
                .triangleAssembly = {
                    .type = TriangleAssemblyCommand::Type::Scale,
                    .value =
                    {
                        .float3 = { x, y, z }
                    }
                }
            }
        }
    );
};

extern "C" int positionCameraTriangleAssembly(float x, float y, float z) {
    return handle.command
    (
        {
            Preset::Name::TriangleAssembly,
            {
                .triangleAssembly = {
                    .type = TriangleAssemblyCommand::Type::PositionCamera,
                    .value =
                    {
                        .float3 = { x, y, z }
                    }
                }
            }
        }
    );
};

extern "C" int lookAtTriangleAssembly(float x, float y, float z) {
    return handle.command
    (
        {
            Preset::Name::TriangleAssembly,
            {
                .triangleAssembly = {
                    .type = TriangleAssemblyCommand::Type::LookAt,
                    .value =
                    {
                        .float3 = { x, y, z }
                    }
                }
            }
        }
    );
};

extern "C" int setProjectionTypeTriangleAssembly(int type) {
    return handle.command
    (
        {
            Preset::Name::TriangleAssembly,
            {
                .triangleAssembly = {
                    .type = TriangleAssemblyCommand::Type::Projection,
                    .value = { .intVal = type }
                }
            }
        }
    );
};

extern "C" int onTriangleAssemblyUpdated(
    CallbackVI onProjectionTypeUpdated,
    CallbackVFFF onPositionChanged,
    CallbackVFFF onScaleChanged,
    CallbackVFFF onCameraPositionChanged,
    CallbackVFFF onTargetChanged
) {
    handle.setPresetCallbacks({ Preset::Name::TriangleAssembly,
    {
        .triangleAssembly = { onProjectionTypeUpdated, onPositionChanged,
            onScaleChanged, onCameraPositionChanged, onTargetChanged }
    }});
    return 1;
};
