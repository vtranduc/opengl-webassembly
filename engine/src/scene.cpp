#include "../headers/scene.h"

Scene::Scene() { renderer = new Renderer(&camera); }

void Scene::render() {
    renderer->clear();
    for (auto buffer : meshBuffers) renderer->renderMesh(buffer);
}

void Scene::add(Mesh& mesh) { meshBuffers.push_back(renderer->processMesh(mesh)); };

void Scene::add(PointLight& light) { lightBuffers.points.push_back(renderer->processLight(light)); };

void Scene::add(DirectionalLight& light) { lightBuffers.directionals.push_back(renderer->processLight(light)); };

Camera& Scene::getCamera() { return camera; };