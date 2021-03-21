#pragma once

#include "SFML/Graphics/RenderTarget.hpp"

#include "World.hpp"

class GameStateChanger;

class GameState
{
public:
	GameState(GameStateChanger& stateChanger, World& world) noexcept;
	virtual ~GameState() = default;

	virtual void onEnter() noexcept = 0;
	virtual void onLeave() noexcept = 0;

	virtual void processLogic(const sf::Time& dt) noexcept = 0;

	virtual void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept;
	virtual void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept;

	virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept;
	virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept;
	virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept;

	virtual void onClosed() noexcept;

	virtual void onEscapePressed() noexcept;

	GameStateChanger& getStateChanger() noexcept;
	World& getWorld() noexcept;

private:
	GameStateChanger& mStateChanger;
	World& mWorld;
};
