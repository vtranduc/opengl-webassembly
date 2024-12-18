#include "../../headers/materials/cel.h"

Cel::Cel() : Material(Shader::Vertex::SphereMirror, Shader::Fragment::Cel, 7) {
    addUniform(&colorUniform);
}