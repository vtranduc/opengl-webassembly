#pragma once

#include <iostream>

using namespace std;

class Shader {
    public:

    enum class Vertex : uint32_t {
        Basic = 0,
        Standard = 1,
        VertexColor = 2,
        SpheresAndLights = 3,
        Extrude = 4,
        VaryingWorldPosition = 5,
        BasicPP = 6,
        SphereMirror = 7
    };

    enum class Fragment : uint32_t {
        Mono = 0,
        VertexColor = 1,
        SpheresAndLights = 2,
        Grid = 3,
        BasicPP = 4,
        InvertPP = 5,
        MonochromePP = 6,
        SphereMirror = 7
    };

    static const int nVertex = 8;

    static const int nFragment = 8;

    static constexpr Vertex vertexList[nVertex] = { Vertex::Basic, Vertex::Standard, Vertex::VertexColor, Vertex::SpheresAndLights, Vertex::Extrude, Vertex::VaryingWorldPosition, Vertex::BasicPP, Vertex::SphereMirror };

    static constexpr Fragment fragmentList[nFragment] = { Fragment::Mono, Fragment::VertexColor, Fragment::SpheresAndLights, Fragment::Grid, Fragment::BasicPP, Fragment::InvertPP, Fragment::MonochromePP, Fragment::SphereMirror };

    static string getFileName(Vertex shader) {
        switch (shader) {
            case Shader::Vertex::Basic: return "basic.glsl";
            case Shader::Vertex::Standard: return "standard.glsl";
            case Shader::Vertex::VertexColor: return "vertexColor.glsl";
            case Shader::Vertex::SpheresAndLights: return "spheresAndLights.glsl";
            case Shader::Vertex::Extrude: return "extrude.glsl";
            case Shader::Vertex::VaryingWorldPosition: return "varyingWorldPosition.glsl";
            case Shader::Vertex::BasicPP: return "basic.pp.glsl";
            case Shader::Vertex::SphereMirror: return "sphereMirror.glsl";
            default: throw "Vertex shader's filename does not exist";
        }
    }

    static string getFileName(Fragment shader) {
        switch (shader) {
            case Shader::Fragment::Mono: return "mono.glsl";
            case Shader::Fragment::VertexColor: return "vertexColor.glsl";
            case Shader::Fragment::SpheresAndLights: return "spheresAndLights.glsl";
            case Shader::Fragment::Grid: return "grid.glsl";
            case Shader::Fragment::BasicPP: return "basic.pp.glsl";
            case Shader::Fragment::InvertPP: return "invert.pp.glsl";
            case Shader::Fragment::MonochromePP: return "monochrome.pp.glsl";
            case Shader::Fragment::SphereMirror: return "sphereMirror.glsl";
            default: throw "Fragment shader's filename does not exist";
        }
    }
};