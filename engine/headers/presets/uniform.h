#pragma once

#include <iostream>

struct ColorTriangleCommand {
    enum Type : uint32_t {
        Color = 0
    };

    union Value {
        int intVal;
    };

    struct Data {
        Type type;
        Value value;
    };
};

struct TriangleAssemblyCommand {
    enum Type : uint32_t {
        Color = 0,
        Translate = 1,
        Scale = 2,
        PositionCamera = 3,
        LookAt = 4,
        Projection = 5
    };

    union Value {
        int intVal;

        float float3[3];
    };

    struct Data {
        Type type;
        Value value;
    };
};

struct SpheresAndLightsCommand {
    enum Type : uint32_t {
        CameraRight = 0,
        CameraLeft = 1,
        CameraUp = 2,
        CameraDown = 3
    };

    struct Data {
        Type type;
    };
};

union CommandData {
    ColorTriangleCommand::Data colorTriangle;

    TriangleAssemblyCommand::Data triangleAssembly;

    SpheresAndLightsCommand::Data spheresAndLights;
};