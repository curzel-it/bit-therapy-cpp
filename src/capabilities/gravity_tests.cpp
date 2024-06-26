#include <gtest/gtest.h>
#include <chrono>

#include "../game/game.h"

#include "gravity.h"
#include "linear_movement.h"

TEST(GravityTests, CanChangeEntityDirection) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    Gravity gravity(1000.0);
    gravity.update(std::chrono::milliseconds(100), entity);
    EXPECT_FLOAT_EQ(entity->direction.y, 0.981);
};

TEST(GravityTests, WillStopWhenGroundIsReached) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    double groundY = 1000.0;
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<Gravity>(groundY));

    entity->update(std::chrono::milliseconds(100));
    entity->update(std::chrono::milliseconds(100));
    entity->update(std::chrono::milliseconds(100));
    entity->update(std::chrono::milliseconds(100));
    entity->update(std::chrono::milliseconds(100));
    EXPECT_FLOAT_EQ(entity->direction.x, 1.0);
    EXPECT_FLOAT_EQ(entity->direction.y, 0.0);
    EXPECT_FLOAT_EQ(entity->frame.y, groundY - entity->frame.h);
};