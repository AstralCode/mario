#include "GameStateManager.hpp"

GameStateManager::GameStateManager(GameContextData& gameData) :
	mGameData{gameData}
{

}

void GameStateManager::AddPushStateRequest(const GameStateIdentifiers gameStateIdentifier)
{

}

void GameStateManager::AddPopStateRequest()
{

}

void GameStateManager::AddClearStatesRequest()
{

}

void GameStateManager::ProcessRequests()
{

}

void GameStateManager::ProcessEvents(const sf::Event& event)
{

}

void GameStateManager::ProcessLogic()
{

}

void GameStateManager::ProcessRender(sf::RenderTarget& renderer) const
{

}

unsigned int GameStateManager::GetActiveStateCount() const
{
	return 0u;
}
