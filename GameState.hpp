#pragma once

#include "SFML/Graphics/RenderTarget.hpp"

#include "EventReceiver.hpp"
#include "TilemapView.hpp"
#include "TilemapEditor.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "GameObjectCreator.hpp"
#include "GameObject.hpp"

class GameContextData;
class GameStateChanger;

class GameState : public EventReceiver
{
public:
	GameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger) noexcept;
	virtual ~GameState() = default;

	virtual void onEnter() noexcept = 0;
	virtual void onLeave() noexcept = 0;

	virtual void processLogic(const sf::Time& frameTime) noexcept = 0;

	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept override;
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept override;
	void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept override;

	void onClosed() noexcept override;

	void onEscapePressed() noexcept override;

	TilemapView& getTilemapView() noexcept;
	TilemapEditor& getTilemapEditor() noexcept;
	ResourceContainer& getResourceContainer() noexcept;
	SpritesetContainer& getSpritesetContainer() noexcept;
	GameObjectCreator& getGameObjectCreator() noexcept;

protected:
	const sf::Font& getFont(const FontIdentifiers identifier) noexcept;
	const sf::Texture& getTexture(const TextureIdentifiers identifier) noexcept;

	GameContextData& mGameContextData;
	GameStateChanger& mGameStateChanger;
};
