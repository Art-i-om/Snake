cmake_minimum_required(VERSION 3.31)
project(Snake)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
)

add_executable(
        Snake src/main.cpp
        src/Input.cpp
        src/Input.hpp
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

FetchContent_MakeAvailable(SFML)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
