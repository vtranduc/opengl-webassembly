#include "../headers/scene.h"

Scene::Scene() { renderer = new Renderer(&camera); }

void Scene::render() {
    renderer->clear();
    for (auto buffer : meshBuffers) renderer->renderMesh(buffer);
}

void Scene::add(Mesh& mesh) { meshBuffers.push_back(renderer->processMesh(mesh)); };

Camera& Scene::getCamera() { return camera; };