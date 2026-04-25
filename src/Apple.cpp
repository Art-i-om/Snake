#include "Apple.hpp"
#include <cmath>

Apple::Apple(float cellSize, sf::Vector2i gridPos)
    : cellSize(cellSize),
      gridPosition(gridPos),
      animationTimer(0.0f),
      pulseSpeed(10.0f)
{
    float radius = cellSize / 2.f;
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin({radius, radius});
    updateShapePosition();
}

void Apple::setGridPosition(const sf::Vector2i& pos) {
    gridPosition = pos;
    updateShapePosition();
}

sf::Vector2i Apple::getGridPosition() const {
    return gridPosition;
}

sf::Vector2f Apple::getPosition() const {
    return shape.getPosition();
}

void Apple::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Apple::update(const float &dt) {
    animationTimer += dt;

    float scale = 1.0f + 0.1f * std::sin(animationTimer * pulseSpeed);
    shape.setScale({scale, scale});
}

void Apple::updateShapePosition() {
    float x = static_cast<float>(gridPosition.x) * cellSize + cellSize / 2.f;
    float y = static_cast<float>(gridPosition.y) * cellSize + cellSize / 2.f;
    shape.setPosition({x, y});
}
