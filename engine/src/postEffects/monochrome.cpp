#include "../../headers/postEffects/monochrome.h"

Monochrome::Monochrome() : PostEffect(Shader::Vertex::BasicPP, Shader::Fragment::MonochromePP) {}