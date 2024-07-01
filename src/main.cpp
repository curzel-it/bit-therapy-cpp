#include <QApplication>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>

#include "args/args.h"
#include "game/game.h"
#include "pets/pets.h"
#include "rendering/rendering.h"
#include "species/species.h"
#include "sprites/sprites.h"
#include "utils/utils.h"

static const double GAME_FPS = 30.0;
static const double UI_FPS = 30.0;
static const double ANIMATIONS_FPS = 10.0;
static const double BASE_ENTITY_SIZE = 50.0;

static const std::string SPECIES_PATH = "/Users/curzel/dev/bit-therapy/Species";
static const std::string ASSETS_PATH = "/Users/curzel/dev/bit-therapy/PetsAssets";

static SpriteSetBuilder* spriteSetBuilder = new SpriteSetBuilder();
static SpritesRepository* spritesRepo = new SpritesRepository(spriteSetBuilder);
static SpeciesParser* speciesParser = new SpeciesParser();
static SpeciesRepository* speciesRepo = new SpeciesRepository(speciesParser);
static PetsBuilder* petsBuilder = new PetsBuilder(speciesRepo, spritesRepo, ANIMATIONS_FPS, BASE_ENTITY_SIZE);

std::vector<std::thread> gameThreads;

std::vector<Screen> screensMatching(const Arguments& args);
std::vector<std::string> selectedSpecies(const Arguments& args);

void joinGameThreads();
std::thread startGameLoop(Game* game);

void startGame(    
    bool debugEnabled,
    double scaleMultiplier,
    double speedMultiplier,
    Screen screen, 
    std::vector<std::string> species
);

void startGames(
    bool debugEnabled,
    double scaleMultiplier,
    double speedMultiplier,
    std::vector<Screen> screens, 
    std::vector<std::string> species
);

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    spritesRepo->setup(ASSETS_PATH);
    speciesRepo->setup(SPECIES_PATH);

    auto args = parseArgs(argc, argv);
    if (args.help) {
        return EXIT_SUCCESS;
    }
    auto screens = screensMatching(args);
    auto species = selectedSpecies(args);

    startGames(
        args.debug, 
        args.scale, 
        args.speed, 
        screens, 
        species
    );

    // AppWindow appWindow;
    // appWindow.show();

    auto result = app.exec();

    joinGameThreads();
    return result;
}

void joinGameThreads() {
    for (auto& t : gameThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

void startGames(
    bool debugEnabled,
    double scaleMultiplier,
    double speedMultiplier,
    std::vector<Screen> screens, 
    std::vector<std::string> species
) {
    for (const Screen& screen : screens) {
        startGame(debugEnabled, scaleMultiplier, speedMultiplier, screen, species);
    }
}

void startGame(    
    bool debugEnabled,
    double scaleMultiplier,
    double speedMultiplier,
    Screen screen, 
    std::vector<std::string> species
) {
    Game* game = new Game(
        spritesRepo, speciesRepo, 
        screen.name, screen.frame,
        GAME_FPS, ANIMATIONS_FPS, 
        scaleMultiplier * BASE_ENTITY_SIZE
    );

    auto entities = compactMap<std::string, Entity*>(
        species, [screen, speedMultiplier, scaleMultiplier](const std::string species) {
            return petsBuilder->build(
                scaleMultiplier, 
                speedMultiplier, 
                species, 
                screen.frame
            );
        }
    );
    game->addEntities(entities);

    GameWindow* window = new GameWindow(UI_FPS, game, debugEnabled, screen.name, screen.frame);
    window->show();

    auto newThread = startGameLoop(game);
    gameThreads.push_back(std::move(newThread));
}

std::vector<Screen> screensMatching(const Arguments& args) {
    if (!args.screens.empty()) {
        auto screens = screensMatching(args.screens);

        if (screens.empty()) {
            std::cerr << "No matching screens found! The following one(s) should be available:" << std::endl;

            for (const Screen& screen : listAvailableScreens()) {
                std::cerr << "  - " << screen.description() << std::endl;
            }
            std::exit(EXIT_FAILURE);
        }
        return screens;
    } else {
        auto screens = listAvailableScreens();
        if (screens.empty()) {
            std::cerr << "No screen found!" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        return screens;
    }
}

std::vector<std::string> selectedSpecies(const Arguments& args) {
    if (!args.species.empty()) {
        return args.species;
    } else {
        std::cerr << "No species selected, please run with `--species ape` or something" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

std::thread startGameLoop(Game* game) {
    return std::thread([game]() {
        bool gameIsRunning = true;
        auto frameDuration = std::chrono::milliseconds(uint32_t(1000 / game->gameFps));
        
        while (gameIsRunning) { 
            auto frameStart = std::chrono::steady_clock::now();
            game->update(frameDuration);
            auto frameEnd = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
            
            auto sleepDuration = frameDuration - elapsedTime;
            if (sleepDuration > std::chrono::milliseconds(0)) {
                std::this_thread::sleep_for(sleepDuration);
            }
        }
    });
}
