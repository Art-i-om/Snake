#pragma once

#include <SFML/Graphics.hpp>

class SnakePart {
public:
    SnakePart(SnakePart* next = nullptr, float cellSize = 20.f, sf::Vector2f startPos = {0.f, 0.f});

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::Vector2i getCell() const;

    void draw(sf::RenderWindow& window);
    void update();

private:
    sf::RectangleShape shape;
    std::pair<int, int> coords;
    SnakePart* nextPart;
    float cellSize;
};