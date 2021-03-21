#pragma once

#include "GameState.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameStateChanger& stateChanger, World& world) noexcept;

	void onEnter() noexcept override;
	void onLeave() noexcept override;

	void processLogic(const sf::Time& dt) noexcept override;

private:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) noexcept override;
	void onEscapePressed() noexcept override;
};
