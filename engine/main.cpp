#include <iostream>
#include <emscripten.h>
#include "headers/webglHandle.h"

#include <filesystem>

#include <fstream>
#include <string>

using namespace std;

static WebGLHandle handle;

// namespace fs = std::filesystem;


extern "C" const char* sayHello(char* name, int repeat) {
    string str;
    for (int i = 0; i <= repeat; i++) str += "Hello, " + (string)name + "!\n";
    const char* ptr = str.c_str();
    return ptr;
}

extern "C" int initialize(char* canvasId, int clearColor) {
    FILE *fp;
    long size = 0;
    char* shaderContent;

    fp = fopen("basic.glsl", "rb");
    if (fp == NULL) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }


    // std::cout << "Current path is " << fs::current_path() << '\n';


    ifstream  f("basic.glsl");

    // fileStream.open(("basicdfadsfdss.glsl"));

    // if (f.fail()) {
    //     cout << "failed??? 55555555555" << endl;
    // }

    if (f.is_open())
    {
        // while ( getline (myfile,line) )
        // {
        //     cout << line << '\n';
        // }
        // myfile.close();

        cout << "ok w" << endl;
    }

    else cout << "Unable to open file BED\n";


    return handle.initialize(canvasId, clearColor);
}

extern "C" int setClearColor(int color) {
    return handle.setClearColor(color);
}

int main() {
    cout << "Hello World" << endl;
    return 1;
}