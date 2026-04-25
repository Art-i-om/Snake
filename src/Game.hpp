#pragma once

#include <SFML/Graphics.hpp>

#include "FullSnake.hpp"
#include "FoodSystem.hpp"

enum class GameState {
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
    void restart();

    void initWindow();
    void initSnake();
    void initFoodSystem();
    void initUI();

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
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Text restartText;
};
