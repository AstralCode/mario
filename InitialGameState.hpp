#pragma once

#include "GameState.hpp"
#include "GameObjectFactory.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameContextData& contextData) noexcept;

	void onEnter() noexcept override;
	void onLeave() noexcept override;

	void processLogic(const sf::Time& fixedFrameTime) noexcept override;

private:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onEscapePressed() noexcept override;

	GameObjectFactory mGameObjectFactory;
};
