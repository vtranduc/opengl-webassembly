#include "../../headers/presets/staticGLTF.h"

void StaticGLTF::init() {
    ifstream in("assets/characters/seeu_miniature/scene.gltf", ios::binary);
    if (!in) throw "Failed to load asset!";
    std::string contents, tmp;
    while (getline(in, tmp)) contents.append(tmp);
    in.close();
    json JSON = json::parse(contents);
};

void StaticGLTF::set() {
    setDirty();
};

void StaticGLTF::command(const CommandData& data) {};

void StaticGLTF::render() {
    PresetBase::render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void StaticGLTF::setCallbacks(const Callbacks& callbacks) {};