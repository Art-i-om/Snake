#include "FoodSystem.hpp"
#include <algorithm>
#include <iostream>

FoodSystem::FoodSystem(float cellSize, int gridWidth, int gridHeight)
    : cellSize(cellSize),
      gridWidth(gridWidth),
      gridHeight(gridHeight),
      gen(rd())
{
}

void FoodSystem::spawnApple() {
    sf::Vector2i pos = getRandomFreePosition();
    apples.emplace_back(cellSize, pos);
}

void FoodSystem::draw(sf::RenderWindow& window) {
    for (auto& apple : apples) {
        apple.draw(window);
    }
}

void FoodSystem::update(const float &dt) {
    for (auto& apple : apples) {
        apple.update(dt);
    }
}

bool FoodSystem::checkCollision(const sf::Vector2i& snakeHeadCell) {
    for (auto it = apples.begin(); it != apples.end(); ++it) {
        if (it->getGridPosition() == snakeHeadCell) {
            apples.erase(it);
            return true;
        }
    }
    return false;
}

void FoodSystem::addOccupiedCell(const sf::Vector2i& cell) {
    occupiedCells.push_back(cell);
}

void FoodSystem::clearOccupiedCells() {
    occupiedCells.clear();
}

sf::Vector2i FoodSystem::getRandomFreePosition() {
    std::uniform_int_distribution<> disX(0, gridWidth - 1);
    std::uniform_int_distribution<> disY(0, gridHeight - 1);

    sf::Vector2i pos;
    int attempts = 0;
    const int maxAttempts = 1000;

    do {
        pos = {disX(gen), disY(gen)};
        attempts++;

        if (attempts >= maxAttempts) {
            break;
        }
    } while (isCellOccupied(pos));

    return pos;
}

bool FoodSystem::isCellOccupied(const sf::Vector2i& cell) const {
    return std::find(occupiedCells.begin(), occupiedCells.end(), cell) != occupiedCells.end();
}

void FoodSystem::reset() {
    apples.clear();
}
