#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <format>
#include <mutex>
#include <string>
#include <vector>

#include "entity.h"
#include "geometry.h"

#include "../sprites/sprites.h"
#include "../species/species.h"

struct RenderedItem {
    uint32_t id;
    std::string spritePath;
    Rect frame;
    bool isFlipped;

    RenderedItem(uint32_t id, std::string spritePath, Rect frame, bool isFlipped);
};

class Game {    
private:
    std::mutex mtx;
    
    const SpritesRepository* spritesRepo;
    const SpeciesRepository* speciesRepo;
    const double animationFps;
    const double baseEntitySize;
    const Rect bounds;

    std::vector<Entity*> entities;

public:
    const double gameFps;
    const std::string screenName;
    
    Game(
        const SpritesRepository* spritesRepo,
        const SpeciesRepository* speciesRepo,
        std::string screenName,
        Rect bounds,
        double gameFps, 
        double animationFps, 
        double baseEntitySize
    );
    
    void update(std::chrono::milliseconds timeSinceLastUpdate);    
    void addEntity(Entity* entity);    
    void addEntities(const std::vector<Entity*> entities);
    const uint32_t numberOfEntities();
    std::vector<RenderedItem> render();
    std::string description();
};

#endif
