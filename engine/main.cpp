#include <iostream>
#include <emscripten.h>

using namespace std;

 extern "C" const char* sayHello(char* name, int repeat) {
    string str;
    for (int i = 0; i <= repeat; i++) str += "Hello, " + (string)name + "!\n";
    const char* ptr = str.c_str();
    return ptr;
 }

int main() {
    cout << "Hello World" << endl;
    return 1;
}