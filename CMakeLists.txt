cmake_minimum_required(VERSION 3.31)
project(Snake)
set(CMAKE_CXX_STANDARD 23)

find_package(SFML REQUIRED COMPONENTS Graphics Window System Audio Network)
add_subdirectory(libs/Input)

add_executable(
        Snake src/main.cpp
        src/Game.cpp
        src/Game.hpp
        src/SnakePart.cpp
        src/SnakePart.hpp
        src/SnakeHead.cpp
        src/SnakeHead.hpp
        src/FullSnake.cpp
        src/FullSnake.hpp
        src/Apple.cpp
        src/Apple.hpp
        src/FoodSystem.cpp
        src/FoodSystem.hpp
        src/Constants.hpp
)

target_link_libraries(Snake PRIVATE
        Input
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
)
