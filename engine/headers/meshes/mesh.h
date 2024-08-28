#pragma once

#include "../object3D.h"
#include "../geometry.h"
#include "../material.h"

class Mesh : public Object3D {

public:

    Mesh() = default;

    Mesh(Geometries geometry, Materials material);

    Mesh(Geometry* geometry, Material* material = new MonoMaterial());

    struct RenderData {
        Geometry::RenderData geometry;

        Material::RenderData material;
    };

    RenderData getRenderData() const;

    const vector<Material::UniformData*> getUniforms() const;

private:

    Geometry* geometry = nullptr;
    Material* material = nullptr;
};