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

GameResourceContainer& GameState::getGameResourceContainer()
{
	return mGameContextData.getGameResourceContainer();
}

GameSpriteAtlasManager& GameState::getGameSpriteAtlasManager()
{
	return mGameContextData.getGameSpriteAtlasManager();
}

GameObjectCreator& GameState::getGameObjectCreator()
{
	return mGameContextData.getGameObjectCreator();
}

const sf::Font& GameState::getFont(const FontIdentifiers identifier)
{
	return getGameResourceContainer().getFont(identifier);
}

const sf::Texture& GameState::getTexture(const TextureIdentifiers identifier)
{
	return getGameResourceContainer().getTexture(identifier);
}
