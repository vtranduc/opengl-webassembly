#include "../../headers/presets/threeBabylonConcept.h"

void ThreeBabylonConcept::init() {
    Mesh* sphere = new Mesh(Geometries::Sphere,  Materials::SphereMirror);
    scene.add(*sphere);
    float position[3] = { -1.0f, 1.0f, 1.0f };
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

    PostEffect* monochromePostEffect = new Monochrome();
    scene.add(*monochromePostEffect);

    PostEffect* blurPostEffect = new Blur();
    scene.add(*blurPostEffect);
};

void ThreeBabylonConcept::set() { setDirty(); };

void ThreeBabylonConcept::cleanUp() {};

void ThreeBabylonConcept::command(const CommandData& data) {
    switch (data.threeBabylonConcept.type) {
    case ThreeBabylonConceptCommand::Type::TogglePostProcessing:
        if (++postEffectIndex > 2) postEffectIndex = -1;
        scene.enbalePostEffect(postEffectIndex);
        setDirty();
        break;
    default: break;
    }
};

void ThreeBabylonConcept::render() {
    PresetBase::render();
    scene.render();
};