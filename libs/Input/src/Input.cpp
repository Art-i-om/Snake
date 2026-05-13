#include "../include/Input.hpp"

#include <iostream>

void Input::update(const sf::RenderWindow& window) {
    m_keyPrevious   = m_keyCurrent;
    m_mousePrevious = m_mouseCurrent;

    m_mousePrevPos = m_mousePos;
    m_mousePos     = sf::Mouse::getPosition(window);

    m_scrollDelta     = m_scrollDeltaNext;
    m_scrollDeltaNext = 0.f;
}

void Input::handleEvent(const sf::Event &event) {
    if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
        m_keyCurrent[static_cast<int>(e->code)] = true;
    }
    else if (const auto* e = event.getIf<sf::Event::KeyReleased>()) {
        m_keyCurrent[static_cast<int>(e->code)] = false;
    }

    if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
        m_mouseCurrent[static_cast<int>(e->button)] = true;
    }
    else if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
        m_mouseCurrent[static_cast<int>(e->button)] = false;
    }

    if (const auto* e = event.getIf<sf::Event::MouseMoved>()) {
        m_mousePos = e->position;
    }

    if (const auto* e = event.getIf<sf::Event::MouseWheelScrolled>()) {
        m_scrollDeltaNext += e->delta;
    }
}

bool Input::isKeyPressed(sf::Keyboard::Key key) const {
    const int k = static_cast<int>(key);

    auto cur  = m_keyCurrent.find(k);
    auto prev = m_keyPrevious.find(k);

    bool curDown  = cur  != m_keyCurrent.end()  && cur->second;
    bool prevDown = prev != m_keyPrevious.end()  && prev->second;

    return curDown && !prevDown;
}

bool Input::isKeyReleased(sf::Keyboard::Key key) const
{
    const int k = static_cast<int>(key);

    auto cur  = m_keyCurrent.find(k);
    auto prev = m_keyPrevious.find(k);

    bool curDown  = cur  != m_keyCurrent.end()  && cur->second;
    bool prevDown = prev != m_keyPrevious.end()  && prev->second;

    return !curDown && prevDown;
}

bool Input::isKeyHeld(sf::Keyboard::Key key) const
{
    auto it = m_keyCurrent.find(static_cast<int>(key));
    return it != m_keyCurrent.end() && it->second;
}

bool Input::isMousePressed(sf::Mouse::Button btn) const
{
    const int b = static_cast<int>(btn);

    auto cur  = m_mouseCurrent.find(b);
    auto prev = m_mousePrevious.find(b);

    bool curDown  = cur  != m_mouseCurrent.end()  && cur->second;
    bool prevDown = prev != m_mousePrevious.end()  && prev->second;

    return curDown && !prevDown;
}

bool Input::isMouseReleased(sf::Mouse::Button btn) const
{
    const int b = static_cast<int>(btn);

    auto cur  = m_mouseCurrent.find(b);
    auto prev = m_mousePrevious.find(b);

    bool curDown  = cur  != m_mouseCurrent.end()  && cur->second;
    bool prevDown = prev != m_mousePrevious.end()  && prev->second;

    return !curDown && prevDown;
}

bool Input::isMouseHeld(sf::Mouse::Button btn) const
{
    auto it = m_mouseCurrent.find(static_cast<int>(btn));
    return it != m_mouseCurrent.end() && it->second;
}

sf::Vector2i Input::getMousePositioni() const
{
    return m_mousePos;
}

sf::Vector2f Input::getMousePositionf(const sf::RenderWindow& window) const
{
    return window.mapPixelToCoords(m_mousePos);
}

sf::Vector2i Input::getMouseDelta() const
{
    return m_mousePos - m_mousePrevPos;
}

float Input::getScrollDelta() const
{
    return m_scrollDelta;
}