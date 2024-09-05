#pragma once

#include "math/matrix/view.h"
#include "math/matrix/projection.h"
#include "light.h"
#include "object3D.h"
#include "mesh.h"
#include "light.h"
#include "postEffect.h"
#include "renderer.h"
#include "camera.h"
#include <vector>
#include <iostream>

using namespace std;

class Scene : public Object3D {

public:

    Scene();

    void render();

    void add(Mesh& mesh);

    void add(PointLight& light);

    void add(DirectionalLight& light);

    void add(PostEffect& postEffect);

    Camera& getCamera();

private:

    Camera camera;

    Renderer* renderer = nullptr;

    vector<Renderer::MeshBufferData> meshBuffers;

    struct lightBuffers {
        vector<Renderer::LightBufferData::Point> points;

        vector<Renderer::LightBufferData::Directional> directionals;
    }lightBuffers;

    vector<Renderer::PostEffectBufferData> postEffectBuffers;
};