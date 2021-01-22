#include "GameState.hpp"

GameState::GameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) :
	mGameContextData{gameContextData},
	mGameStateChanger{gameStateChanger}
{

}

void GameState::onKeyPressed(const sf::Event::KeyEvent&)
{

}

void GameState::onKeyReleased(const sf::Event::KeyEvent&)
{

}

void GameState::onMouseButtonPressed(const sf::Event::MouseButtonEvent&)
{

}

void GameState::onMouseButtonReleased(const sf::Event::MouseButtonEvent&)
{

}

void GameState::onMouseMoved(const sf::Event::MouseMoveEvent&)
{

}

void GameState::onClosed()
{

}

GraphicsItem& GameState::getGraphicsScene()
{
	return mGraphicsScene;
}
