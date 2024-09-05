#include "../../headers/postEffects/postEffect.h"

PostEffect::PostEffect(Shader::Vertex vertex, Shader::Fragment fragment) {
    renderData.shader.vertex = vertex;
    renderData.shader.fragment = fragment;
}

PostEffect::RenderData PostEffect::getRenderData() const { return renderData; };