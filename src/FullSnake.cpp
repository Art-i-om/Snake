#include "FullSnake.hpp"

#include <algorithm>

#include "Constants.hpp"

FullSnake::FullSnake(SnakeHead *head)
    : head(head),
      direction({1, 0}),
      nextDirection({1, 0}),
      stepTimer(0.f),
      stepInterval(GameConstants::BASE_STEP_INTERVAL),
      cellSize(GameConstants::CELL_SIZE),
      gridWidth(GameConstants::GRID_WIDTH),
      gridHeight(GameConstants::GRID_HEIGHT),
      pendingGrowth(0)
{

}

void FullSnake::setHead(SnakeHead *newHead) {
    head = newHead;
}

void FullSnake::grow(int amount) {
    pendingGrowth += amount;
}

void FullSnake::setStepInterval(float newInterval) {
    stepInterval = std::max(newInterval, GameConstants::MIN_STEP_INTERVAL);
}

sf::Vector2i FullSnake::getHeadCell() const {
    if (head) {
        return head->getCell();
    }
    return {0, 0};
}

void FullSnake::handleEvent(sf::Event& event) {
    input.handleEvent(event);
}

void FullSnake::handleDirectionInput() {
    if (input.isKeyPressed(sf::Keyboard::Key::W) || input.isKeyPressed(sf::Keyboard::Key::Up)) {
        if (direction != sf::Vector2i{0, 1}) nextDirection = {0, -1};
    }
    else if (input.isKeyPressed(sf::Keyboard::Key::S) || input.isKeyPressed(sf::Keyboard::Key::Down)) {
        if (direction != sf::Vector2i{0, -1}) nextDirection = {0, 1};
    }
    else if (input.isKeyPressed(sf::Keyboard::Key::A) || input.isKeyPressed(sf::Keyboard::Key::Left)) {
        if (direction != sf::Vector2i{1, 0}) nextDirection = {-1, 0};
    }
    else if (input.isKeyPressed(sf::Keyboard::Key::D) || input.isKeyPressed(sf::Keyboard::Key::Right)) {
        if (direction != sf::Vector2i{-1, 0}) nextDirection = {1, 0};
    }
}

void FullSnake::moveOneStep() {
    if (!head) {
        return;
    }

    direction = nextDirection;

    const sf::Vector2f oldHeadPos = head->getPosition();
    const sf::Vector2f delta{direction.x * cellSize, direction.y * cellSize};
    sf::Vector2f newHeadPos = oldHeadPos + delta;

    if (newHeadPos.x < 0.f) {
        newHeadPos.x = (gridWidth - 1) * cellSize;
    } else if (newHeadPos.x >= gridWidth * cellSize) {
        newHeadPos.x = 0.f;
    }

    if (newHeadPos.y < 0.f) {
        newHeadPos.y = (gridHeight - 1) * cellSize;
    } else if (newHeadPos.y >= gridHeight * cellSize) {
        newHeadPos.y = 0.f;
    }

    std::vector<sf::Vector2f> oldBodyPos;
    oldBodyPos.reserve(body.size());
    for (const auto& part : body) {
        oldBodyPos.push_back(part.getPosition());
    }

    head->setPosition(newHeadPos);

    if (!body.empty()) {
        body[0].setPosition(oldHeadPos);
        for (std::size_t i = 1; i < body.size(); i++) {
            body[i].setPosition(oldBodyPos[i - 1]);
        }
    }

    if (pendingGrowth > 0) {
        sf::Vector2f tailSpawn = oldHeadPos;
        if (!oldBodyPos.empty()) {
            tailSpawn = oldBodyPos.back();
        }
        body.emplace_back(nullptr, cellSize, tailSpawn);
        --pendingGrowth;
    }
}

void FullSnake::draw(sf::RenderWindow& window) {
    if (head) head->draw(window);
    for (auto& snakePart : body) {
        snakePart.draw(window);
    }
}

void FullSnake::update(sf::RenderWindow& window, float& dt) {
    handleDirectionInput();

    stepTimer += dt;
    while (stepTimer >= stepInterval) {
        moveOneStep();
        stepTimer -= stepInterval;
    }

    input.update(window);
}

bool FullSnake::checkCollision() const {
    for (auto it = body.begin(); it < body.end(); ++it) {
        if (it->getCell() == head->getCell()) {
            return true;
        }
    }

    return false;
}

void FullSnake::reset() {
    body.clear();
    direction = {1, 0};
    nextDirection = {1, 0};
    stepTimer = 0.f;
    stepInterval = GameConstants::BASE_STEP_INTERVAL;
    pendingGrowth = 0;

    if (head) {
        head->setPosition({100.f, 100.f});
    }
}

