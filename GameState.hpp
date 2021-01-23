#pragma once

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "EventReceiver.hpp"
#include "GraphicsItem.hpp"

class GameContextData;
class GameStateChanger;

class GameState : public EventReceiver, private sf::NonCopyable
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

	GraphicsItem& getGraphicsScene();

protected:
	GameContextData& mGameContextData;
	GameStateChanger& mGameStateChanger;
	GraphicsItem mGraphicsScene;
};
