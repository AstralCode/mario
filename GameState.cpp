#include "GameState.hpp"

GameState::GameState(GameContextData& contextData, GameStateChanger& stateChanger) noexcept :
	mContextData{contextData},
	mStateChanger{stateChanger}
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

GameContextData& GameState::getContextData() noexcept
{
	return mContextData;
}

GameStateChanger& GameState::getStateChanger() noexcept
{
	return mStateChanger;
}
