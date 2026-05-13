#include "../src/Game.hpp"
#include <iostream>
#include <algorithm>

#include "Constants.hpp"

Game::Game()
    : applesEaten(0),
      gameState(GameState::Menu),
      gridLines(sf::PrimitiveType::Lines),
      timerText(font),
      scoreText(font),
      titleText(font),
      playButtonText(font),
      exitButtonText(font),
      finalScoreText(font),
      gameOverText(font),
      restartText(font)
{
    if (!font.openFromFile("C:/Users/Artello/CLionProjects/Snake/src/fonts/Teethreedee Back Std.otf")) {
        std::cerr << "couldn't load font from file\n";
        return;
    }

    initWindow();
    initSnake();
    initFoodSystem();
    initUI();
    initGrid();
}

Game::~Game() = default;

void Game::initWindow() {
    window.create(sf::VideoMode({GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT}), "SFML Window");
}

void Game::initSnake() {
    snake.setHead(&snakeHead);
    snake.grow(GameConstants::SNAKE_INITIAL_LENGTH);
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

    titleText.setFont(font);
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color::Green);
    titleText.setString("Snake");
    titleText.setPosition({265.f, 110.f});

    playButton.setSize({220.f, 70.f});
    playButton.setPosition({290.f, 260.f});
    playButton.setFillColor(sf::Color(40, 110, 40));
    playButton.setOutlineThickness(2.f);
    playButton.setOutlineColor(sf::Color::White);

    playButtonText.setFont(font);
    playButtonText.setCharacterSize(32);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setString("Play");
    playButtonText.setPosition({365.f, 275.f});

    exitButton.setSize({220.f, 70.f});
    exitButton.setPosition({290.f, 360.f});
    exitButton.setFillColor(sf::Color(110, 40, 40));
    exitButton.setOutlineThickness(2.f);
    exitButton.setOutlineColor(sf::Color::White);

    exitButtonText.setFont(font);
    exitButtonText.setCharacterSize(32);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setString("Exit");
    exitButtonText.setPosition({370.f, 375.f});

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition({265.f, 130.f});
    gameOverText.setString("Game Over");

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(GameConstants::FONT_SIZE);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition({300.f, 220.f});
    finalScoreText.setString("");

    restartText.setFont(font);
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition({220.f, 320.f});
    restartText.setString("Press Space to restart or Esc for menu");
}

void Game::initGrid() {
    gridLines.clear();

    for (int x = 0; x <= GameConstants::GRID_WIDTH; ++x) {
        const float xPos = x * GameConstants::CELL_SIZE;
        gridLines.append(sf::Vertex{{xPos, 0.f}, sf::Color(35, 35, 35)});
        gridLines.append(sf::Vertex{{xPos, static_cast<float>(GameConstants::WINDOW_HEIGHT)}, sf::Color(35, 35, 35)});
    }

    for (int y = 0; y <= GameConstants::GRID_HEIGHT; ++y) {
        const float yPos = y * GameConstants::CELL_SIZE;
        gridLines.append(sf::Vertex{{0.f, yPos}, sf::Color(35, 35, 35)});
        gridLines.append(sf::Vertex{{static_cast<float>(GameConstants::WINDOW_WIDTH), yPos}, sf::Color(35, 35, 35)});
    }
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::update() {
    if (gameState != GameState::Playing) {
        frameClock.restart();
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
        updateSpeed();
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
        case GameState::Menu:
            renderMenu();
            break;
        case GameState::Playing:
            renderPlaying();
            break;
        case GameState::GameOver:
            renderGameOver();
            break;
    }

    window.display();
}

void Game::renderMenu() {
    window.draw(gridLines);
    window.draw(titleText);
    window.draw(playButton);
    window.draw(playButtonText);
    window.draw(exitButton);
    window.draw(exitButtonText);
}

void Game::renderPlaying() {
    window.draw(gridLines);
    foodSystem.draw(window);
    snake.draw(window);

    window.draw(timerText);
    window.draw(scoreText);
}

void Game::renderGameOver() {
    window.draw(gridLines);
    window.draw(gameOverText);
    window.draw(finalScoreText);
    window.draw(restartText);
}

void Game::processEvents() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            updateMenuHover(window.mapPixelToCoords(mouseMoved->position));
        }

        if (gameState == GameState::Menu) {
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    const sf::Vector2f clickPosition = window.mapPixelToCoords(mousePressed->position);
                    if (isPointInsideButton(playButton, clickPosition)) {
                        startGame();
                    } else if (isPointInsideButton(exitButton, clickPosition)) {
                        window.close();
                    }
                }
            }
        } else if (gameState == GameState::GameOver) {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    restart();
                } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    gameState = GameState::Menu;
                }
            }
        } else {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    gameState = GameState::Menu;
                    frameClock.restart();
                    continue;
                }
            }
            snake.handleEvent(*event);
        }
    }
}

void Game::startGame() {
    restart();
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
    snake.grow(GameConstants::SNAKE_INITIAL_LENGTH);
    updateSpeed();

    foodSystem.reset();
    foodSystem.spawnApple();

    scoreText.setString("Apples: 0");
    timerText.setString("Time: 0:00");

    gameTimer.restart();
    frameClock.restart();
}

void Game::updateSpeed() {
    const int speedLevel = applesEaten / GameConstants::APPLES_PER_SPEED_LEVEL;
    const float stepInterval = GameConstants::BASE_STEP_INTERVAL -
        speedLevel * GameConstants::STEP_INTERVAL_DECREASE;
    snake.setStepInterval(stepInterval);
}

void Game::updateMenuHover(const sf::Vector2f& mousePosition) {
    const bool overPlay = isPointInsideButton(playButton, mousePosition);
    const bool overExit = isPointInsideButton(exitButton, mousePosition);

    playButton.setFillColor(overPlay ? sf::Color(60, 150, 60) : sf::Color(40, 110, 40));
    exitButton.setFillColor(overExit ? sf::Color(150, 60, 60) : sf::Color(110, 40, 40));
}

bool Game::isPointInsideButton(const sf::RectangleShape& button, const sf::Vector2f& point) const {
    return button.getGlobalBounds().contains(point);
}
