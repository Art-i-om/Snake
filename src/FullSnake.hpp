#pragma once
#include <vector>

#include "Input.hpp"
#include "SnakeHead.hpp"
#include "SnakePart.hpp"

class FullSnake {
public:
    FullSnake(SnakeHead* head = nullptr);

    void update(sf::RenderWindow& window, float& dt);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);

    void setHead(SnakeHead* newHead);
    void grow(int amount = 1);
    sf::Vector2i getHeadCell() const;
    bool checkCollision() const;
    void reset();

private:
    void handleDirectionInput();
    void moveOneStep();


    std::vector<SnakePart> body;
    SnakeHead* head;
    Input input;

    sf::Vector2i direction;
    sf::Vector2i nextDirection;

    float stepTimer;
    float stepInterval;
    float cellSize;

    int pendingGrowth;
};
