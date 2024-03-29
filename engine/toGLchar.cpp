#include <fstream>
#include "headers/shader.h"

using namespace std;

int main() {
    ifstream f;
    string line;
    string tab1 = "    ", tab2 = tab1 + tab1, tab3 = tab1 + tab2;

    // Headers

    string content =
        "#include <iostream>\n"
        "#include <GLES3/gl3.h>\n"
        "#include \"shader.h\"\n"
        "using namespace std;\n\n";

    // Vertex shaders

    content += "static const GLchar* getShaderSource(Shader::Vertex shader) {\n";
    content += tab1 + "switch (static_cast<int>(shader)) {\n";
    for (int i = 0; i < Shader::nVertex; i++) {
        Shader::Vertex shader = Shader::vertexList[i];
        f.open("glsl/vertex/" + Shader::getFileName(shader));
        if (!f.is_open()) throw "Unable to open glsl file";
        content += tab2 + "case " + to_string(static_cast<int>(shader)) + ": return";
        while (!f.eof()) {
            content += "\n";
            getline(f, line);
            content += tab3 + "\"";
            content += line;
            content += "\\n\"";
        }
        content += ";\n";
        f.close();
    }
    content += tab2 + "default: return \"\";\n" + tab1 + "};\n};\n\n";

    // Fragment shaders

    content += "static const GLchar* getShaderSource(Shader::Fragment shader) {\n";
    content += tab1 + "switch (static_cast<int>(shader)) {\n";

    for (int i = 0; i < Shader::nFragment; i++) {
        Shader::Fragment shader = Shader::fragmentList[i];
        f.open("glsl/fragment/" + Shader::getFileName(shader));
        if (!f.is_open()) throw "Unable to open glsl file";
        content += tab2 + "case " + to_string(static_cast<int>(shader)) + ": return";
        while (!f.eof()) {
            content += "\n";
            getline(f, line);
            content += tab3 + "\"";
            content += line;
            content += "\\n\"";
        }
        content += ";\n";
        f.close();
    }

    content += tab2 + "default: return \"\";\n" + tab1 + "};\n};\n";

    // Write source file

    ofstream o("headers/shaderSource.h");
    if (!o.is_open()) throw "Unable to create glsl handle file";
    o << content;
    o.close();
    return 1;
}