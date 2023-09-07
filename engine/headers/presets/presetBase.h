#pragma once

#include "uniform.h"

#include <iostream>

using namespace std;

class PresetBase {
    private:
    
    bool dirty;

    public:

    virtual void init() = 0;

    virtual void set() = 0;

    virtual void command(const CommandData& data) = 0;

    virtual void render();

    bool isDirty() const;

    protected:

    void setDirty();
};

