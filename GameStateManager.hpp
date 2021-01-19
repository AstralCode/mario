#pragma once

#include "GameState.hpp"
#include "GameStateIdentifiers.hpp"

class GameStateManager final : private sf::NonCopyable
{
public:
	GameStateManager(GameContextData& gameData);

	template<typename TGameState>
	void RegisterState(const GameStateIdentifiers gameStateIdentifier);

	void AddPushStateRequest(const GameStateIdentifiers gameStateIdentifier);
	void AddPopStateRequest();
	void AddClearStatesRequest();

	void ProcessRequests();

	void ProcessEvents(const sf::Event& event);
	void ProcessLogic();
	void ProcessRender(sf::RenderTarget& renderer) const;

	unsigned int GetActiveStateCount() const;

private:
	GameContextData& mGameData;
};

template<typename TGameState>
inline void GameStateManager::RegisterState(const GameStateIdentifiers gameStateIdentifier)
{

}
