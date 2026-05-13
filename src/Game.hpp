#pragma once

#include <SFML/Graphics.hpp>

#include "FullSnake.hpp"
#include "FoodSystem.hpp"

enum class GameState {
    Menu,
    Playing,
    GameOver
};

class Game {
public:
    void run();

    Game();
    ~Game();

private:
    void update();
    void render();
    void processEvents();
    void gameOver();
    void startGame();
    void restart();

    void initWindow();
    void initSnake();
    void initFoodSystem();
    void initUI();
    void initGrid();

    void updateSpeed();
    void updateMenuHover(const sf::Vector2f& mousePosition);
    bool isPointInsideButton(const sf::RectangleShape& button, const sf::Vector2f& point) const;

    void renderMenu();
    void renderPlaying();
    void renderGameOver();

    sf::RenderWindow window;
    sf::Clock frameClock;
    sf::Clock gameTimer;

    SnakeHead snakeHead;
    FullSnake snake;
    FoodSystem foodSystem;

    sf::Font font;
    sf::Text timerText;
    sf::Text scoreText;
    int applesEaten;

    GameState gameState;
    sf::VertexArray gridLines;
    sf::Text titleText;
    sf::RectangleShape playButton;
    sf::Text playButtonText;
    sf::RectangleShape exitButton;
    sf::Text exitButtonText;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Text restartText;
};
