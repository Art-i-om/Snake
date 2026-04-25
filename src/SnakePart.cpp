#include "SnakePart.hpp"

SnakePart::SnakePart(SnakePart *next, float cellSize, sf::Vector2f startPos)
    : nextPart(next), cellSize(cellSize)
{
    shape.setSize({cellSize, cellSize});
    shape.setFillColor(sf::Color(120, 200, 120));
    shape.setPosition(startPos);
}

void SnakePart::setPosition(const sf::Vector2f &pos) {
    shape.setPosition(pos);
    coords = {static_cast<int>(pos.x / cellSize), static_cast<int>(pos.y / cellSize)};
}

sf::Vector2f SnakePart::getPosition() const {
    return shape.getPosition();
}

sf::Vector2i SnakePart::getCell() const {
    return {coords.first, coords.second};
}

void SnakePart::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void SnakePart::update() {

}
