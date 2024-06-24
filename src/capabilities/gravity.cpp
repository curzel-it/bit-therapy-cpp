#include "gravity.h"

#include <chrono>

#include "../game/game.h"

void Gravity::update(std::chrono::milliseconds timeSinceLastUpdate, Entity * entity) {
    double timeStep = timeSinceLastUpdate.count() / 1000.0;
    Vector2d gravity_effect = gravity_acceleration * timeStep;
    entity->direction = entity->direction + gravity_effect;
}