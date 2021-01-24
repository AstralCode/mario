#include "GameState.hpp"

#include "GameContextData.hpp"

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

void GameState::onEscapePressed()
{

}

GraphicsItem& GameState::getGraphicsScene()
{
	return mGameContextData.getGraphicsScene();
}

GameResourceContainer& GameState::getResourceContainer()
{
	return mGameContextData.getResourceContainer();
}

GameObjectCreator& GameState::getGameObjectCreator()
{
	return mGameContextData.getGameObjectCreator();
}

const sf::Font& GameState::getFont(const FontIdentifiers identifier)
{
	return getResourceContainer().getFont(identifier);
}

const sf::Texture& GameState::getTexture(const TextureIdentifiers identifier)
{
	return getResourceContainer().getTexture(identifier);
}
