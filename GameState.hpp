#pragma once

#include "SFML/Graphics/RenderTarget.hpp"

#include "EventReceiver.hpp"
#include "ResourceContainer.hpp"
#include "SpritesetContainer.hpp"
#include "GraphicsScene.hpp"

class GameContextData;
class GameStateChanger;

class GameState : public EventReceiver
{
public:
	GameState(GameContextData& contextData) noexcept;
	virtual ~GameState() = default;

	virtual void onEnter() noexcept = 0;
	virtual void onLeave() noexcept = 0;

	virtual void processLogic(const sf::Time& dt) noexcept = 0;

	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onKeyReleased(const sf::Event::KeyEvent& keyEvent) noexcept override;

	void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept override;
	void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent) noexcept override;
	void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent) noexcept override;

	void onClosed() noexcept override;

	void onEscapePressed() noexcept override;

	ResourceContainer& getResources() noexcept;
	SpritesetContainer& getSpritesets() noexcept;
	GraphicsScene& getScene() noexcept;
	GameStateChanger& getStateChanger() noexcept;

protected:
	const sf::Font& getFont(const Fonts identifier) noexcept;
	const sf::Texture& getTexture(const Textures identifier) noexcept;

	GameContextData& mContextData;
};
