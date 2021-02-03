#pragma once

#include "SFML/Graphics/RenderTarget.hpp"

#include "EventReceiver.hpp"
#include "TiledMap.hpp"
#include "GameResourceContainer.hpp"
#include "GameSpriteAtlasManager.hpp"
#include "GameObjectCreator.hpp"
#include "GameObject.hpp"

class GameContextData;
class GameStateChanger;

class GameState : public EventReceiver
{
public:
	GameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger);
	virtual ~GameState() = default;

	virtual void onEnter() = 0;
	virtual void onLeave() = 0;

	virtual void processLogic(const sf::Time& frameTime) = 0;

	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) override;

	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButtonEvent) override;
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent) override;
	void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent) override;

	void onClosed() override;

	void onEscapePressed() override;

	TiledMap& getTiledMap();
	GraphicsItem& getGraphicsScene();
	GameResourceContainer& getGameResourceContainer();
	GameSpriteAtlasManager& getGameSpriteAtlasManager();
	GameObjectCreator& getGameObjectCreator();

protected:
	const sf::Font& getFont(const FontIdentifiers identifier);
	const sf::Texture& getTexture(const TextureIdentifiers identifier);

	GameContextData& mGameContextData;
	GameStateChanger& mGameStateChanger;
};
