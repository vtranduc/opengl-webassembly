#include <iostream>
#include <GLES3/gl3.h>
using namespace std;

const  GLchar* basic_vertex = 
"precision highp float;\n"
"\n"
"attribute vec3 position;\n"
"\n"
"void main() {\n"
"    gl_Position = vec4(position, 1.0);\n"
"}\n"
;
