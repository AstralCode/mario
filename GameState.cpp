#include "GameState.hpp"

#include "GameContextData.hpp"

GameState::GameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) noexcept :
	mGameContextData{gameContextData},
	mGameStateChanger{gameStateChanger}
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

TilemapView& GameState::getTilemapView() noexcept
{
	return mGameContextData.getTilemapView();
}

ResourceContainer& GameState::getResourceContainer() noexcept
{
	return mGameContextData.getResourceContainer();
}

SpritesetContainer& GameState::getSpritesetContainer() noexcept
{
	return mGameContextData.getSpritesetContainer();
}

GameObjectCreator& GameState::getGameObjectCreator() noexcept
{
	return mGameContextData.getGameObjectCreator();
}

const sf::Font& GameState::getFont(const FontIdentifiers identifier) noexcept
{
	return getResourceContainer().getFont(identifier);
}

const sf::Texture& GameState::getTexture(const TextureIdentifiers identifier) noexcept
{
	return getResourceContainer().getTexture(identifier);
}
