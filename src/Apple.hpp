#pragma once

#include <SFML/Graphics.hpp>

class Apple {
public:
    Apple(float cellSize = 20.f, sf::Vector2i gridPos = {0, 0});

    void setGridPosition(const sf::Vector2i& pos);
    sf::Vector2i getGridPosition() const;
    sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window);
    void update(const float& dt);

private:
    float cellSize;
    sf::Vector2i gridPosition;
    sf::CircleShape shape;

    float animationTimer;
    float pulseSpeed;

    void updateShapePosition();
};

