#include "../../headers/materials/sphereMirror.h"

SphereMirror::SphereMirror() : Material(Shader::Vertex::SphereMirror, Shader::Fragment::SphereMirror, 7) {
    addUniform(&colorUniform);
}