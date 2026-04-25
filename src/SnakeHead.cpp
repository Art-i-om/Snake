#include "SnakeHead.hpp"

SnakeHead::SnakeHead(float cellSize, sf::Vector2f startPos)
    : cellSize(cellSize)
{
    shape.setSize({cellSize, cellSize});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(startPos);
}

void SnakeHead::setPosition(const sf::Vector2f &pos) {
    shape.setPosition(pos);
}

sf::Vector2f SnakeHead::getPosition() const {
    return shape.getPosition();
}

sf::Vector2i SnakeHead::getCell() const {
    const sf::Vector2f p = shape.getPosition();
    return {static_cast<int>(p.x / cellSize), static_cast<int>(p.y / cellSize)};
}

void SnakeHead::draw(sf::RenderWindow &window) {
        window.draw(shape);
}


void SnakeHead::update() {

}
