#include "GameState.hpp"

GameState::GameState(GameStateChanger& stateChanger, World& world) noexcept :
	mStateChanger{stateChanger},
	mWorld{world}
{

}

void GameState::onKeyPressed(const sf::Event::KeyEvent&) noexcept
{

}

void GameState::onKeyReleased(const sf::Event::KeyEvent&) noexcept
{

}

void GameState::onMouseButtonPressed(const sf::Event::MouseButtonEvent&) noexcept
{

}

void GameState::onMouseButtonReleased(const sf::Event::MouseButtonEvent&) noexcept
{

}

void GameState::onMouseMoved(const sf::Event::MouseMoveEvent&) noexcept
{

}

void GameState::onClosed() noexcept
{

}

void GameState::onEscapePressed() noexcept
{

}

GameStateChanger& GameState::getStateChanger() noexcept
{
	return mStateChanger;
}

World& GameState::getWorld() noexcept
{
	return mWorld;
}
