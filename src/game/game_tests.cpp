#include <chrono>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

#include "../config_tests.h"
#include "../capabilities/capabilities.h"
#include "../species/species.h"
#include "../sprites/sprites.h"

#include "game.h"
#include "geometry.h"

TEST(GameTests, CanUpdateCascade) {
    std::vector<RenderedItem> results({});
    Game* game = new Game(
        nullptr, nullptr,         
        "test", Rect(0.0, 0.0, 100.0, 100.0), 
        10.0, 10.0, 50.0
    );

    auto spriteSet = SpriteSet(
        std::map<std::string, std::vector<std::string>>({
            {SPRITE_NAME_MOVEMENT, {"walk-0", "walk-1", "walk-2"}}, 
            {SPRITE_NAME_DRAG, {"drag-0", "drag-1", "drag-2"}},
            {SPRITE_NAME_FRONT, {"front-0", "front-1", "front-2"}},
        })
    );
    Rect initialFrame = Rect(0.0, 0.0, 1.0, 1.0);        
    Species species("test", 1.0, 1.0);            

    Entity ape(0, 10.0, 50.0, 1.0, &species, &spriteSet, initialFrame);
    game->addEntity(&ape); 
    
    auto linearMovement = std::make_shared<LinearMovement>();
    ape.addCapability(linearMovement);

    game->update(std::chrono::milliseconds(100));
    results = game->render();
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].frame.x, 0.06);

    game->update(std::chrono::milliseconds(100));
    results = game->render();
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].frame, Rect(0.12, 0.0, 1.0, 1.0));

    game->update(std::chrono::milliseconds(100));
    results = game->render();
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].frame, Rect(0.18, 0.0, 1.0, 1.0));

    game->update(std::chrono::milliseconds(100));
    results = game->render();
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].frame, Rect(0.24, 0.0, 1.0, 1.0));

    game->update(std::chrono::milliseconds(100));
    results = game->render();
    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].frame, Rect(0.3, 0.0, 1.0, 1.0));
};