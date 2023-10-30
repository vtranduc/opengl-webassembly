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
        LookAt = 4
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

union CommandData {
    ColorTriangleCommand::Data colorTriangle;

    TriangleAssemblyCommand::Data triangleAssembly;
};