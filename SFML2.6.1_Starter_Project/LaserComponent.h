#include "SFML/System/Vector2.hpp"
#include "WindowManager.h"
#pragma once

class Laser;

class LaserComponent {
    protected:
    Laser* entity = nullptr;

    public:
    void setParent(Laser* parent) {
        this->entity = parent;
    }

    virtual void init() { }

    virtual void update(float dt) { }
};
