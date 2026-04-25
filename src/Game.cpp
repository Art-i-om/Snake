#include "../src/Game.hpp"

#include <iostream>

#include "Constants.hpp"

Game::Game()
    : applesEaten(0), timerText(font), scoreText(font), finalScoreText(font), gameOverText(font), restartText(font)
{
    if (!font.openFromFile("C:/Users/Artello/CLionProjects/Snake/src/fonts/Teethreedee Back Std.otf")) {
        std::cerr << "couldn't load font from file\n";
        return;
    }

    gameState = GameState::Playing;
    initWindow();
    initSnake();
    initFoodSystem();
    initUI();
}

Game::~Game() = default;

void Game::initWindow() {
    window.create(sf::VideoMode({GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT}), "SFML Window");
}

void Game::initSnake() {
    snake.setHead(&snakeHead);
    snake.grow(3);
}

void Game::initFoodSystem() {
    foodSystem.spawnApple();
}

void Game::initUI() {
    timerText.setFont(font);
    timerText.setCharacterSize(GameConstants::FONT_SIZE);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition({10.f, 10.f});
    timerText.setString("Time: 0:00");

    scoreText.setFont(font);
    scoreText.setCharacterSize(GameConstants::FONT_SIZE);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 40.f});
    scoreText.setString("Apples: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(GameConstants::FONT_SIZE);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition({400.f, 80.f});
    gameOverText.setString("Game Over");

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(GameConstants::FONT_SIZE);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition({400.f, 110.f});
    finalScoreText.setString("");

    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition({400.f, 180.f});
    restartText.setString("Press Space to restart");
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::update() {
    if (gameState == GameState::GameOver) {
        return;
    }

    float deltaTime = frameClock.restart().asSeconds();
    snake.update(window, deltaTime);
    foodSystem.update(deltaTime);

    if (snake.checkCollision()) {
        gameOver();
        return;
    }

    if (foodSystem.checkCollision(snake.getHeadCell())) {
        snake.grow(1);
        foodSystem.spawnApple();
        applesEaten++;
        scoreText.setString("Apples: " + std::to_string(applesEaten));
    }

    const float elapsedTime = gameTimer.getElapsedTime().asSeconds();
    const int minutes = static_cast<int>(elapsedTime) / 60;
    const int seconds = static_cast<int>(elapsedTime) % 60;
    timerText.setString("Time: " + std::to_string(minutes) + ":" +
                        (seconds < 10 ? "0" : "") + std::to_string(seconds));
}

void Game::render() {
    window.clear(sf::Color::Black);

    switch (gameState) {
        case GameState::Playing:
            renderPlaying();
            break;
        case GameState::GameOver:
            renderGameOver();
            break;
    }

    window.display();
}

void Game::renderPlaying() {
    foodSystem.draw(window);
    snake.draw(window);

    window.draw(timerText);
    window.draw(scoreText);
}

void Game::renderGameOver() {
    window.draw(gameOverText);
    window.draw(finalScoreText);
    window.draw(restartText);
}

void Game::processEvents() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (gameState == GameState::GameOver) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    restart();
                }
            }
        } else {
            snake.handleEvent(*event);
        }
    }
}

void Game::gameOver() {
    gameState = GameState::GameOver;

    float elapsedTime = gameTimer.getElapsedTime().asSeconds();
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;

    std::string timeStr = std::to_string(minutes) + ":" +
                          (seconds < 10 ? "0" : "") + std::to_string(seconds);

    finalScoreText.setString("Apples Eaten: " + std::to_string(applesEaten) +
                             "\nTime: " + timeStr);
}

void Game::restart() {
    gameState = GameState::Playing;
    applesEaten = 0;

    snake.reset();
    snake.grow(3);

    foodSystem.reset();
    foodSystem.spawnApple();

    scoreText.setString("Apples: 0");
    timerText.setString("Time: 0:00");

    gameTimer.restart();
    frameClock.restart();
}
