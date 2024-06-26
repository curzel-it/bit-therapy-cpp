#include <gtest/gtest.h>
#include <chrono>
#include <iostream>

#include "../game/game.h"

#include "linear_movement.h"
#include "wall_crawler.h"

TEST(WallCrawlerTests, WillStartGoingUpAfterReachingRightBound) {
    Rect gameBounds(0.0, 0.0, 1000.0, 1000.0);
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(1.0, 0.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<WallCrawler>(gameBounds));

    entity->frame.x = 899.0;
    entity->update(std::chrono::milliseconds(10));
    EXPECT_FLOAT_EQ(entity->direction.x, 0.0);
    EXPECT_FLOAT_EQ(entity->direction.y, -1.0);
};

TEST(WallCrawlerTests, WillStartGoingLeftAfterReachingTopBound) {
    Rect gameBounds(0.0, 0.0, 1000.0, 1000.0);
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(0.0, -1.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<WallCrawler>(gameBounds));

    entity->frame.x = 900.0;
    entity->frame.y = 1.0;
    entity->update(std::chrono::milliseconds(10));
    EXPECT_FLOAT_EQ(entity->direction.x, -1.0);
    EXPECT_FLOAT_EQ(entity->direction.y, 0.0);
};

TEST(WallCrawlerTests, WillStartGoingDownAfterReachingLeftBound) {
    Rect gameBounds(0.0, 0.0, 1000.0, 1000.0);
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(-1.0, 0.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<WallCrawler>(gameBounds));

    entity->frame.x = 1.0;
    entity->frame.y = 0.0;
    entity->update(std::chrono::milliseconds(10));
    EXPECT_FLOAT_EQ(entity->direction.x, 0.0);
    EXPECT_FLOAT_EQ(entity->direction.y, 1.0);
};

TEST(WallCrawlerTests, WillStartGoingRightAfterReachingBottomBound) {
    Rect gameBounds(0.0, 0.0, 1000.0, 1000.0);
    Species species("test", 100.0, 1.0);
    SpriteSet sprites;

    Entity* entity = new Entity(0, 1.0, 100.0, 1.0, &species, &sprites, Rect(0.0, 0.0, 100.0, 100.0));
    entity->direction = Vector2d(0.0, 1.0);
    
    entity->addCapability(std::make_shared<LinearMovement>());
    entity->addCapability(std::make_shared<WallCrawler>(gameBounds));

    entity->frame.x = 0.0;
    entity->frame.y = 899.0;
    entity->update(std::chrono::milliseconds(10));
    EXPECT_FLOAT_EQ(entity->direction.x, 1.0);
    EXPECT_FLOAT_EQ(entity->direction.y, 0.0);
};