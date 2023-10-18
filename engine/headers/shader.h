#pragma once

#include <iostream>

using namespace std;

class Shader {
    public:

    enum class Vertex : uint32_t {
        Basic = 0,
        Standard = 1
    };

    enum class Fragment : uint32_t {
        Mono = 0
    };

    static const int nVertex = 2;

    static const int nFragment = 1;

    static constexpr Vertex vertexList[nVertex] = { Vertex::Basic, Vertex::Standard };

    static constexpr Fragment fragmentList[nFragment] = { Fragment::Mono };

    static string getFileName(Vertex shader) {
        switch (shader) {
            case Shader::Vertex::Basic: return "basic.glsl";
            case Shader::Vertex::Standard: return "standard.glsl";
            default: throw "Vertex shader's filename does not exist";
        }
    }

    static string getFileName(Fragment shader) {
        switch (shader) {
            case Shader::Fragment::Mono: return "mono.glsl";
            default: throw "Fragment shader's filename does not exist";
        }
    }
};