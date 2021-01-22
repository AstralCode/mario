#pragma once

#include "GameState.hpp"

class InitialGameState final : public GameState
{
public:
	using GameState::GameState;

	void onEnter() override;
	void onLeave() override;

	void processLogic(const sf::Time& frameTime) override;

private:
	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) override;

	void onClosed() override;
};
