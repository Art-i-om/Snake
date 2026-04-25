#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class SnakeHead {
public:
    SnakeHead(float cellSize = 20.f, sf::Vector2f startPos = {100.f, 100.f});

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::Vector2i getCell() const;

    void update();
    void draw(sf::RenderWindow& window);
private:
    float cellSize;
    sf::RectangleShape shape;
};
