#include "InitialGameState.hpp"

#include "GameContextData.hpp"
#include "GameResourceManager.hpp"

InitialGameState::InitialGameState(GameContextData& gameContextData, GameStateManager& gameStateManager) :
	GameState{gameContextData, gameStateManager}
{

}

void InitialGameState::ProcessEvents(const sf::Event& event)
{

}

void InitialGameState::ProcessLogic()
{

}

void InitialGameState::ProcessRender(sf::RenderTarget& renderer) const
{

}
