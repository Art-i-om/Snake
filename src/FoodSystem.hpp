#pragma once

#include <vector>
#include <random>
#include "Apple.hpp"
#include "SnakeHead.hpp"
#include "SnakePart.hpp"

class FoodSystem {
public:
    FoodSystem(float cellSize = 20.f, int gridWidth = 40, int gridHeight = 30);

    void spawnApple();
    void draw(sf::RenderWindow& window);
    void update(const float& dt);

    bool checkCollision(const sf::Vector2i& snakeHeadCell);

    void addOccupiedCell(const sf::Vector2i& cell);
    void clearOccupiedCells();

    void reset();

private:
    std::vector<Apple> apples;
    std::vector<sf::Vector2i> occupiedCells;

    float cellSize;
    int gridWidth;
    int gridHeight;

    std::random_device rd;
    std::mt19937 gen;

    sf::Vector2i getRandomFreePosition();
    bool isCellOccupied(const sf::Vector2i& cell) const;
};

