
cmake_minimum_required(VERSION 3.28)
project(spel_)

set(CMAKE_CXX_STANDARD 23)

# Tell CMake explicitly where to find SFML
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

# Find SFML package
add_executable(spel_ main.cpp
        Window.cpp
        Window.h
        Game.cpp
        Game.h
        Player.cpp
        Player.h
        Guns/LvlOneGun.cpp
        Guns/LvlOneGun.h
        Guns/Ammo/BasicBullet.cpp
        Guns/Ammo/BasicBullet.h
        Guns/Gun.cpp
        Guns/Gun.h
        Guns/Ammo/Bullet.cpp
        Guns/Ammo/Bullet.h
        map/Map.cpp
        map/Map.h
        Enemies/Enemy.cpp
        Enemies/Enemy.h
        Enemies/BasicEnemy.cpp
        Enemies/BasicEnemy.h
        map/Blocks/Ground.cpp
        map/Blocks/Ground.h
        map/Blocks/BasicGround.cpp
        map/Blocks/BasicGround.h
        misc/TextureManager.cpp
        misc/TextureManager.h
        map/Blocks/Walls/Walls.cpp
        map/Blocks/Walls/Walls.h
        Enemies/EnemyHandler.cpp
        Enemies/EnemyHandler.h)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(spel_
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)
