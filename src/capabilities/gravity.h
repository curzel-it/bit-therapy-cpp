#pragma once

#include <chrono>

#include "../game/game.h"

class Gravity : public EntityCapability {
    Vector2d gravity_acceleration;

public:
    Gravity(double gravity_strength = 9.81) : gravity_acceleration(0.0, gravity_strength) {}
    void update(std::chrono::milliseconds timeSinceLastUpdate, Entity * entity) override;
};
