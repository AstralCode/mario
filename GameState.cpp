#include "GameState.hpp"

#include "GameContextData.hpp"

GameState::GameState(GameContextData& contextData, GameStateChanger& gameStateChanger) noexcept :
	mContextData{contextData},
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

ResourceContainer& GameState::getResources() noexcept
{
	return mContextData.getResources();
}

SpritesetContainer& GameState::getSpritesets() noexcept
{
	return mContextData.getSpritesets();
}

GraphicsScene& GameState::getScene() noexcept
{
	return mContextData.getScene();
}

const sf::Font& GameState::getFont(const FontIdentifiers identifier) noexcept
{
	return getResources().getFont(identifier);
}

const sf::Texture& GameState::getTexture(const TextureIdentifiers identifier) noexcept
{
	return getResources().getTexture(identifier);
}
