#include <gtest/gtest.h>
#include <chrono>

#include "../game/game.h"

#include "bounce_when_lateral_bound_is_hit.h"
#include "linear_movement.h"

TEST(BounceOnBoundHitTests, TurnsRightWhenHittingLeft) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<BounceWhenLateralBoundIsHit>(0.0, 1000.0));
    
    entity->frame.x = -1.0;
    entity->direction = Vector2d(-0.8, 0.0);
    entity->update(std::chrono::milliseconds(1));
    EXPECT_FLOAT_EQ(entity->frame.x, 0.0);
    EXPECT_FLOAT_EQ(entity->direction.x, 0.8);
};

TEST(BounceOnBoundHitTests, TurnsLeftWhenHittingRight) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<BounceWhenLateralBoundIsHit>(0.0, 1000.0));
    
    entity->frame.x = 901.0;
    entity->direction = Vector2d(0.8, 0.0);
    entity->update(std::chrono::milliseconds(1));
    EXPECT_FLOAT_EQ(entity->frame.x, 900.0);
    EXPECT_FLOAT_EQ(entity->direction.x, -0.8);
};

TEST(BounceOnBoundHitTests, DoesNotChangeDirectionIfWithinBounds) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    entity->addCapability(std::make_shared<BounceWhenLateralBoundIsHit>(0.0, 1000.0));
    
    entity->frame.x = 900.0;
    entity->direction = Vector2d(0.8, 0.0);
    entity->update(std::chrono::milliseconds(1));
    EXPECT_FLOAT_EQ(entity->frame.x, 900.0);
    EXPECT_FLOAT_EQ(entity->direction.x, 0.8);
};

TEST(BounceOnBoundHitTests, DoesNotChangeDirectionIfAlreadyGoingAway) {
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    entity->addCapability(std::make_shared<BounceWhenLateralBoundIsHit>(0.0, 1000.0));
    
    entity->frame.x = 901.0;
    entity->direction = Vector2d(-0.8, 0.0);
    entity->update(std::chrono::milliseconds(1));
    EXPECT_FLOAT_EQ(entity->frame.x, 901.0);
    EXPECT_FLOAT_EQ(entity->direction.x, -0.8);
};