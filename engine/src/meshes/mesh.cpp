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
    case Materials::SphereMirror:
        material = new SphereMirror();
        break;
    default:
        break;
    }
};

Mesh::Mesh(Geometry* geometry_, Material* material_) : geometry(geometry_), material(material_) {}

Mesh::RenderData Mesh::getRenderData() const { return { geometry->getRenderData(), material->getRenderData() }; }

const vector<Material::UniformData*> Mesh::getUniforms() const { return material->getUniforms(); };