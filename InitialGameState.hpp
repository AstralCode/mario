#pragma once

#include "GameState.hpp"

class InitialGameState final : public GameState
{
public:
	InitialGameState(GameContextData& gameContextData, GameStateManager& gameStateManager);

	void ProcessEvents(const sf::Event& event) override;
	void ProcessLogic() override;
	void ProcessRender(sf::RenderTarget& renderer) const override;
};
