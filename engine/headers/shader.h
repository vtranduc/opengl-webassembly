#pragma once

#include <iostream>

using namespace std;

class Shader {
    public:

    enum class Vertex : uint32_t {
        Basic = 0,
        Standard = 1,
        VertexColor = 2
    };

    enum class Fragment : uint32_t {
        Mono = 0,
        VertexColor = 1
    };

    static const int nVertex = 3;

    static const int nFragment = 2;

    static constexpr Vertex vertexList[nVertex] = { Vertex::Basic, Vertex::Standard, Vertex::VertexColor };

    static constexpr Fragment fragmentList[nFragment] = { Fragment::Mono, Fragment::VertexColor };

    static string getFileName(Vertex shader) {
        switch (shader) {
            case Shader::Vertex::Basic: return "basic.glsl";
            case Shader::Vertex::Standard: return "standard.glsl";
            case Shader::Vertex::VertexColor: return "vertexColor.glsl";
            default: throw "Vertex shader's filename does not exist";
        }
    }

    static string getFileName(Fragment shader) {
        switch (shader) {
            case Shader::Fragment::Mono: return "mono.glsl";
            case Shader::Fragment::VertexColor: return "vertexColor.glsl";
            default: throw "Fragment shader's filename does not exist";
        }
    }
};