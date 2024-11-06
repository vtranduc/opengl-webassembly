#include "../../headers/presets/threeBabylonConcept.h"

void ThreeBabylonConcept::init() {
    Mesh* sphere = new Mesh(Geometries::Sphere,  Materials::Mono);
    scene.add(*sphere);
    float position[3] = { 1.0f, 1.0f, 1.0f };
    float target[3] = { 0.0f, 0.0f, 0.0f };
    scene.getCamera().setPosition(position);
    scene.getCamera().lookAt(target);

    Mesh* grid = new Grid();
    scene.add(*grid);

    PointLight* pointLight = new PointLight();
    DirectionalLight* directionalLight = new DirectionalLight();
    scene.add(*pointLight);
    scene.add(*directionalLight);

    PostEffect* invertPostEffect = new Invert();
    scene.add(*invertPostEffect);
};

void ThreeBabylonConcept::set() { setDirty(); };

void ThreeBabylonConcept::cleanUp() {};

void ThreeBabylonConcept::command(const CommandData& data) {
    switch (data.threeBabylonConcept.type) {
    case ThreeBabylonConceptCommand::Type::TogglePostProcessing:
        postEffectEnabled = !postEffectEnabled;
        scene.enbalePostEffect(postEffectEnabled ? 0 : -1);
        setDirty();
        break;
    default: break;
    }
};

void ThreeBabylonConcept::render() {
    PresetBase::render();
    scene.render();
};