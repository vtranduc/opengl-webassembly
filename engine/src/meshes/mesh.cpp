#include "../../headers/meshes/mesh.h"

Mesh::Mesh(Geometries geometryType, Materials materialType) {
    switch (geometryType) {
    case Geometries::Sphere:
        geometry = new Sphere();
        break;
    default:
        break;
    }

    switch (materialType) {
    case Materials::Mono:
        material = new MonoMaterial();
        break;
    default:
        break;
    }
};

Mesh::RenderData Mesh::getRenderData() const { return { geometry->getRenderData(), material->getRenderData() }; }

const vector<Material::UniformData*> Mesh::getUniforms() const { return material->getUniforms(); };