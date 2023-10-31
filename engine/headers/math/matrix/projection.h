#pragma once

#include "gl.h"

class Projection : public GLMatrix {

private:

    void updateMatrix() override;
};