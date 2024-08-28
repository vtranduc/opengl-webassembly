#include "../../headers/materials/grid.h"

GridMaterial::GridMaterial() : Material(Shader::Vertex::VaryingWorldPosition, Shader::Fragment::Grid) {
    addUniform(&colors.origin);
    addUniform(&colors.major);
    addUniform(&colors.minor);
    addUniform(&colors.x);
    addUniform(&colors.z);
};