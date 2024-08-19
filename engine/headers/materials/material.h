#pragma once

#include "../utils.h"
#include <iostream>
#include <vector>

using namespace std;

class Material {

public:

    struct RenderData {

        enum ExternalUniforms  {
            Projection,
            View,
            World
        };

        struct {
            Shader::Vertex vertex;

            Shader::Fragment fragment;
        }shader;

        vector<ExternalUniforms> requiredExternalUniforms;
    }renderData;

    Material() = delete;

    Material(Shader::Vertex vertex, Shader::Fragment fragment, int requiredExternalUniforms = 7);

    RenderData getRenderData() const;

    struct UniformData {
        const char* name;

        enum Type{
            Color
        }type;

        union {
            int integer;
        }data;
    };

    const vector<UniformData*> getUniforms() const;

protected:

    void addUniform(UniformData* data);

private:

    vector<UniformData*> uniforms;
};