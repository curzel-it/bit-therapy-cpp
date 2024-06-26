cmake_minimum_required(VERSION 3.10)

project(BitTherapy VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_PREFIX_PATH "../qt-6.7.2-static/lib/cmake")

include_directories("src")
include_directories("src/capabilities")
include_directories("src/game")
include_directories("src/pets")
include_directories("src/rendering")
include_directories("src/species")
include_directories("src/sprites")
include_directories("src/utils")

# Get all sources except tests
file(GLOB MAIN_SOURCES "src/*.cpp")
list(FILTER MAIN_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB ARGS_SOURCES "src/args/*.cpp")
list(FILTER ARGS_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB CAPABILITIES_SOURCES "src/capabilities/*.cpp")
list(FILTER CAPABILITIES_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB GAME_SOURCES "src/game/*.cpp")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB PETS_SOURCES "src/pets/*.cpp")
list(FILTER PETS_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB RENDERING_SOURCES "src/rendering/*.cpp")
list(FILTER RENDERING_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB SPECIES_SOURCES "src/species/*.cpp")
list(FILTER SPECIES_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB SPRITES_SOURCES "src/sprites/*.cpp")
list(FILTER SPRITES_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

file(GLOB UTILS_SOURCES "src/utils/*.cpp")
list(FILTER UTILS_SOURCES EXCLUDE REGEX ".*_tests\\.cpp$")

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(Qt6_DIR "../qt-6.7.2-static/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# App executable
add_executable(Main ${MAIN_SOURCES} ${ARGS_SOURCES} ${CAPABILITIES_SOURCES} ${GAME_SOURCES} ${PETS_SOURCES} ${RENDERING_SOURCES} ${SPECIES_SOURCES} ${SPRITES_SOURCES} ${UTILS_SOURCES})
target_link_libraries(Main PRIVATE Qt6::Widgets)

# Google Test
enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# Get all sources except main 
file(GLOB TEST_SOURCES "src/*.cpp")
list(FILTER TEST_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

file(GLOB TEST_ARGS_SOURCES "src/args/*.cpp")

file(GLOB TEST_CAPABILITIES_SOURCES "src/capabilities/*.cpp")

file(GLOB TEST_GAME_SOURCES "src/game/*.cpp")

file(GLOB TEST_PETS_SOURCES "src/pets/*.cpp")

file(GLOB TEST_RENDERING_SOURCES "src/rendering/*.cpp")

file(GLOB TEST_SPECIES_SOURCES "src/species/*.cpp")

file(GLOB TEST_SPRITES_SOURCES "src/sprites/*.cpp")

file(GLOB TEST_UTILS_SOURCES "src/utils/*.cpp")

# Test executable
add_executable(Test ${TEST_SOURCES} ${TEST_ARGS_SOURCES} ${TEST_CAPABILITIES_SOURCES} ${TEST_GAME_SOURCES} ${TEST_PETS_SOURCES} ${TEST_RENDERING_SOURCES} ${TEST_SPECIES_SOURCES} ${TEST_SPRITES_SOURCES} ${TEST_UTILS_SOURCES})
target_link_libraries(Test GTest::GTest GTest::Main Qt6::Widgets)

# Test discovery
gtest_discover_tests(Test)
