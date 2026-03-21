cmake_minimum_required(VERSION 3.16)
project(rpg_game_class LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(rpg_game_class
    src/main.cpp
    src/core/Arena.cpp
    src/entities/Character.cpp
    src/entities/Warrior.cpp
    src/entities/Mage.cpp
    src/spells/SpellEffect.cpp
    src/status/StatusEffect.cpp
    src/systems/Game.cpp
)

target_include_directories(rpg_game_class PRIVATE include)

target_link_libraries(rpg_game_class PRIVATE sfml-graphics sfml-window sfml-system)
