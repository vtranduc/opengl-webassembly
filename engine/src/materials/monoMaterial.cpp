#include "../../headers/materials/monoMaterial.h"

MonoMaterial::MonoMaterial() : Material(Shader::Vertex::Standard, Shader::Fragment::Mono) {
    addUniform(&colorUniform);
}