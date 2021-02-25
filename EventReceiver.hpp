#pragma once

#include "SFML/Window/Event.hpp"

class EventReceiver
{
public:
	virtual ~EventReceiver() = default;

	virtual void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept = 0;
	virtual void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept = 0;

	virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept = 0;
	virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept = 0;
	virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept = 0;

	virtual void onClosed() noexcept = 0;

	virtual void onEscapePressed() noexcept = 0;
};
