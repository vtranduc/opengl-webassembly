#include "../headers/scene.h"

Scene::Scene() { renderer = new Renderer(&camera); }

void Scene::render() {
    renderer->clear();
    if (postEffectIndex >= 0) renderer->preprocessPostEffect(postEffectBuffers[postEffectIndex]);
    for (auto buffer : meshBuffers) renderer->renderMesh(buffer);
    if (postEffectIndex >= 0) renderer->processPostEffect(postEffectBuffers[postEffectIndex]);
}

void Scene::add(Mesh& mesh) { meshBuffers.push_back(renderer->processMesh(mesh)); };

void Scene::add(PointLight& light) { lightBuffers.points.push_back(renderer->processLight(light)); };

void Scene::add(DirectionalLight& light) { lightBuffers.directionals.push_back(renderer->processLight(light)); };

void Scene::add(PostEffect& postEffect) { postEffectBuffers.push_back(renderer->processPostEffect(postEffect)); };

Camera& Scene::getCamera() { return camera; };

void Scene::enbalePostEffect(int index) { postEffectIndex =   (index >= 0 && index < postEffectBuffers.size()) ? index : -1; };