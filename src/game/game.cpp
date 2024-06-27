#include "game.h"

#include <chrono>
#include <iostream>
#include <math.h>
#include <sstream>

#include "geometry.h"
#include "../utils/utils.h"

RenderedItem::RenderedItem(
    uint32_t id, 
    std::string spritePath, 
    Rect frame,
    bool isFlipped,
    double zRotation
) : 
    id(id),
    spritePath(spritePath), 
    frame(frame),
    isFlipped(isFlipped),
    zRotation(zRotation)
{}

Game::Game(
    const SpritesRepository* spritesRepo,
    const SpeciesRepository* speciesRepo,
    std::string screenName,
    Rect bounds,
    double gameFps, 
    double animationFps, 
    double baseEntitySize
) : 
    spritesRepo(spritesRepo), 
    speciesRepo(speciesRepo), 
    screenName(screenName),
    bounds(bounds),
    gameFps(gameFps), 
    animationFps(animationFps), 
    baseEntitySize(baseEntitySize), 
    entities(std::vector<Entity*>({})) 
{}

void Game::update(std::chrono::milliseconds timeSinceLastUpdate) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& entity : entities) {
        entity->update(timeSinceLastUpdate);
    }
}

void Game::addEntities(const std::vector<Entity*> entities) {
    for (Entity* entity : entities) {
        addEntity(entity);
    }
}

void Game::addEntity(Entity* entity) {
    std::lock_guard<std::mutex> lock(mtx);
    entities.push_back(entity);
}

const uint32_t Game::numberOfEntities() {
    std::lock_guard<std::mutex> lock(mtx);
    return entities.size();
}

std::vector<RenderedItem> Game::render() {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<RenderedItem> renderedItems({});
    
    for (const auto& entity : entities) {
        auto item = RenderedItem(
            entity->id,
            entity->currentSpriteFrame(), 
            entity->frame,
            isFlipped(entity),
            rotation(entity)
        );
        renderedItems.push_back(item);
    }
    return renderedItems;
}

double Game::isFlipped(const Entity* entity) {
    return entity->direction.x < 0.0;
}

double Game::rotation(const Entity* entity) {
    if (entity->direction.x == 0.0 && entity->direction.y == 0.0) {
        return 0.0;
    }
    if (entity->direction.x == 0.0 && entity->direction.y < 0.0) {
        return 1.5 * M_PI;
    }
    if (entity->direction.x == 0.0 && entity->direction.y > 0.0) {
        return 0.5 * M_PI;
    }
    if (entity->direction.x <= 0.0 && entity->direction.y == 0.0 && entity->frame.y == bounds.y) {
        return 1.0 * M_PI;
    }
    return 0.0;
}
    
void Game::mouseDragStarted(const uint32_t& targetId) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& entity : entities) {
        if (entity->id == targetId) {
            entity->direction = Vector2d(0.0, 0.0);
            entity->changeSprite(SPRITE_NAME_FALL);
        }
    }    
}

void Game::mouseDragEnded(const uint32_t& targetId, const Vector2d& delta) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& entity : entities) {
        if (entity->id == targetId) {
            auto dx = delta.x > 0 ? 1.0 : -1.0;
            entity->frame = entity->frame.offset(delta);
            entity->frame.x = fmax(entity->frame.x, 0.0);
            entity->frame.x = fmin(entity->frame.x, bounds.w - entity->frame.w);
            entity->frame.y = fmax(entity->frame.y, 0.0);
            entity->frame.y = fmin(entity->frame.y, bounds.h - entity->frame.h);
            entity->direction = Vector2d(dx, 0.0);
            entity->changeSprite(SPRITE_NAME_MOVEMENT);
        }
    }    
}

std::string Game::description() {
    std::lock_guard<std::mutex> lock(mtx);
    std::stringstream ss; 

    ss << "Game @ " << this << std::endl;
    ss << "  Screen: " << screenName << std::endl;
    ss << "  Origin: " << bounds.x << ", " << bounds.y << std::endl;
    ss << "  Size: " << bounds.w << " x " << bounds.h << std::endl;
    ss << "  Entities: " << entities.size() << std::endl << std::endl;

    for (const auto& entity : entities) {
        ss << entity->description() << std::endl;
    }
    return ss.str();
}