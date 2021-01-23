#pragma once

#include "GameState.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameContextData& gameContextData, GameStateChanger& gameStateChanger);

	void onEnter() override;
	void onLeave() override;

	void processLogic(const sf::Time& frameTime) override;

private:
	bool loadResources();

	void onKeyPressed(const sf::Event::KeyEvent& keyEvent) override;
	void onClosed() override;

	bool isResourceLoaded;
};
