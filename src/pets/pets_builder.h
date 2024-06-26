#pragma once

#include <optional>
#include <string>

#include "../game/game.h"
#include "../sprites/sprites.h"

class PetsBuilder {
private:
    uint32_t nextId;
    const SpeciesRepository* speciesRepo;
    const SpritesRepository* spritesRepo;
    const double animationFps;
    const double baseSize;

public:
    PetsBuilder(
        const SpeciesRepository* speciesRepo, 
        const SpritesRepository* spritesRepo,
        const double animationFps,
        const double baseSize
    );

    std::optional<Entity*> build(
        double scaleMultiplier,
        double speedMultiplier,
        const std::string& species,
        const Rect& gameBounds
    );
};