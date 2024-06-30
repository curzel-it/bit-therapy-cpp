#include "sprite_set.h"

#include "config_tests.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

std::vector<std::string> generate_sprite_names(const std::string& base_name, uint32_t count) {
    std::vector<std::string> names;
    for (uint32_t i = 0; i < count; i++) {
        names.push_back(base_name + "-" + std::to_string(i));
    }
    return names;
}

TEST(SpriteSetTests, CanReferenceStandardSprites) {
    std::map<std::string, std::vector<std::string>> animations({
        {SPRITE_NAME_MOVEMENT, generate_sprite_names(SPRITE_NAME_MOVEMENT, 3)},
        {SPRITE_NAME_DRAG, generate_sprite_names(SPRITE_NAME_DRAG, 3)},
        {SPRITE_NAME_FRONT, generate_sprite_names(SPRITE_NAME_FRONT, 3)},
    });

    SpriteSet sprite_set(animations);

    ASSERT_EQ(sprite_set.spriteFrames(SPRITE_NAME_MOVEMENT)[0], "walk-0");
    ASSERT_EQ(sprite_set.spriteFrames(SPRITE_NAME_DRAG)[0], "drag-0");
    ASSERT_EQ(sprite_set.spriteFrames(SPRITE_NAME_FRONT)[0], "front-0");
}

TEST(SpriteSetTests, CanReferenceAnimations) {
    std::map<std::string, std::vector<std::string>> animations;
    animations["jump"] = generate_sprite_names("jump", 5);
    animations["run"] = generate_sprite_names("run", 5);
    animations["slide"] = generate_sprite_names("slide", 5);

    SpriteSet sprite_set(animations);

    ASSERT_EQ(sprite_set.spriteFrames("jump")[0], "jump-0");
    ASSERT_EQ(sprite_set.spriteFrames("run")[0], "run-0");
    ASSERT_EQ(sprite_set.spriteFrames("slide")[0], "slide-0");
}
