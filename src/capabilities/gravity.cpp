#include "gravity.h"

#include <chrono>
#include <iostream>

#include "../game/game.h"

Gravity::Gravity(double groundY) : 
    gravityAcceleration(Vector2d(0, 9.81)),
    groundY(groundY)
{}

void Gravity::update(std::chrono::milliseconds timeSinceLastUpdate, Entity * entity) {
    if (entity->frame.maxY() < groundY) {
        double timeStep = timeSinceLastUpdate.count() / 1000.0;
        Vector2d gravityEffect = gravityAcceleration * timeStep;
        entity->direction = entity->direction + gravityEffect;
    } else {
        entity->frame.y = groundY - entity->frame.h;
        entity->direction = Vector2d(1.0, 0.0);
    }
}