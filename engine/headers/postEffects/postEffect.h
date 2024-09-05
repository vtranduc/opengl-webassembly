#pragma once

#include "../utils.h"

class PostEffect {

public:

    PostEffect(Shader::Vertex vertex, Shader::Fragment fragment);

    struct RenderData {

        struct {
            Shader::Vertex vertex;

            Shader::Fragment fragment;
        }shader;

    };

    RenderData getRenderData() const;

private:

    RenderData renderData;
};