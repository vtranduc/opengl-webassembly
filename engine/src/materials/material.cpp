#include "../../headers/materials/material.h"



Material::Material(Shader::Vertex vertex, Shader::Fragment fragment, int requiredExternalUniformsBits) {
    renderData.shader.vertex = vertex;
    renderData.shader.fragment = fragment;
    if ((requiredExternalUniformsBits & 1) != 0) renderData.requiredExternalUniforms.push_back(RenderData::ExternalUniforms::World);
    if ((requiredExternalUniformsBits & 2) != 0) renderData.requiredExternalUniforms.push_back(RenderData::ExternalUniforms::View);
    if ((requiredExternalUniformsBits & 4) != 0) renderData.requiredExternalUniforms.push_back(RenderData::ExternalUniforms::Projection);
}

Material::RenderData Material::getRenderData() const { return renderData; };

const vector<Material::UniformData*> Material::getUniforms() const { return uniforms; };

void Material::addUniform(UniformData* data) { uniforms.push_back(data); };