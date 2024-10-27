cmake_minimum_required(VERSION 3.29)
project(jogo)

set(CMAKE_CXX_STANDARD 20)

add_executable(jogo main.cpp
        sprites/Sprite.cpp
        sprites/Sprite.h
        game_objects/player/Player.cpp
        game_objects/player/Player.h
        game_objects/laser/Laser.cpp
        game_objects/laser/Laser.h
        game_objects/ovni/Ovni.cpp
        game_objects/ovni/Ovni.h
        configuration/Configuration.cpp
)

target_link_libraries(jogo raylib)
