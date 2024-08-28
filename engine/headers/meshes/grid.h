#pragma once

#include "mesh.h"
#include "../object3D.h"
#include "../geometry.h"
#include "../material.h"

class Grid final : public Mesh {

public:

    Grid();

    Grid(Geometries geometry, Materials material) = delete;

    Grid(Geometry* geometry, Material* material) = delete;
};