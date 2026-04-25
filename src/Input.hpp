#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Input {
public:
    void update(const sf::RenderWindow& window);
    void handleEvent(const sf::Event& event);

    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isKeyReleased(sf::Keyboard::Key key) const;
    bool isKeyHeld(sf::Keyboard::Key key) const;

    bool isMousePressed(sf::Mouse::Button btn) const;
    bool isMouseReleased(sf::Mouse::Button btn) const;
    bool isMouseHeld(sf::Mouse::Button btn) const;

    sf::Vector2i getMousePositioni() const;
    sf::Vector2f getMousePositionf(const sf::RenderWindow& w) const;

    sf::Vector2i getMouseDelta() const;
    float getScrollDelta() const;

private:
    std::unordered_map<int, bool> m_keyCurrent;
    std::unordered_map<int, bool> m_keyPrevious;

    std::unordered_map<int, bool> m_mouseCurrent;
    std::unordered_map<int, bool> m_mousePrevious;

    sf::Vector2i m_mousePos;
    sf::Vector2i m_mousePrevPos;

    float m_scrollDelta     = 0.f;
    float m_scrollDeltaNext = 0.f;
};