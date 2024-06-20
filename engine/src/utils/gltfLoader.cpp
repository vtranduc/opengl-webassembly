#include "../../headers/externalLibs.h"
#include <iostream>

using namespace std;

using namespace tinygltf;

class GLTFStaticMesh {
public:

    Model model;
    pair<unsigned int, map<int, unsigned int>> VAO_and_EBOs;
    float scale;

    GLTFStaticMesh(const char* filename, float scale) {
        cout << "constructing" << endl;

        tinygltf::TinyGLTF loader;
        string error;
        string warning;

        bool ret = loader.LoadASCIIFromFile(&model, &error, &warning, "../../../public/model/characters/seeu_miniature/scene.gltf");

        if (!warning.empty()) {
            printf("Warn: %s\n", warning.c_str());
        }

        if (!error.empty()) {
            printf("Err: %s\n", error.c_str());
        }

        if (!ret) {
            printf("Failed to parse glTF\n");
        }
    };

    ~GLTFStaticMesh() {
        cout << "destructuring" << endl;
    };

private:
    void bindMOdelNodes(map<int, unsigned int>& ebos, Node& node) {

    };

    void bindMesh(map<int, unsigned int>& ebos, Mesh& mesh) {

    };
};

int main() {
    cout << "hello world" << endl;

    GLTFStaticMesh mesh{"hello", 1.0f};

    return 1;
}