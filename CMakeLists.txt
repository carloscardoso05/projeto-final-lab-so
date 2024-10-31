cmake_minimum_required(VERSION 3.29)
project(jogo)

set(CMAKE_CXX_STANDARD 20)

add_executable(jogo main.cpp
        configuration/Configuration.cpp
        raygui.h
        game_objects/worker/Worker.cpp
        game_objects/worker/Worker.h
)

target_link_libraries(jogo raylib)
