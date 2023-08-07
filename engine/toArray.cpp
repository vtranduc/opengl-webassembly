#include <iostream>

using namespace std;

#include <fstream>

int main() {
    cout << "hello world" << endl;

    ifstream f("glsl/vertex/basic.glsl");

    if (f.is_open()) {
        cout << "ok w" << endl;

        string line = "";
        // string content = "";

        // while (!f.eof()) {
        //     getline(f, line);

        //     // cout << line << endl;

        //     content.append(line + "\n");
        // }

        

        // f.close();


        // cout << "final content =======" << endl;

        // cout << content << endl;

        ofstream o("headers/basic.h");

        string cppContent =
            "#include <iostream>\n"
            "#include <GLES3/gl3.h>\n"
            "using namespace std;\n\n"
            "const  GLchar* basic_vertex = \n"
        ;

        while (!f.eof()) {
            getline(f, line);
            // cppContent.append("\"" + "");
            cppContent += "\"";
            cppContent += line;
            cppContent += "\\n\"\n";
        }

        // cppContent.append(content);

        cppContent += ";\n";

        

        o << cppContent;

        f.close();
        o.close();

    } else {
        cout << "failed: " << endl;
    }

    return 1;
}