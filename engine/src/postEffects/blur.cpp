#include "../../headers/postEffects/blur.h"

Blur::Blur() : PostEffect(Shader::Vertex::BasicPP, Shader::Fragment::BlurPP) {}