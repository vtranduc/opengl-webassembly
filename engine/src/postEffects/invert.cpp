#include "../../headers/postEffects/invert.h"

Invert::Invert() : PostEffect(Shader::Vertex::BasicPP, Shader::Fragment::InvertPP) {}