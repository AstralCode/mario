#pragma once

#include <memory>
#include <deque>
#include <queue>
#include <functional>
#include <unordered_map>

#include "GameState.hpp"
#include "GameStateChanger.hpp"
#include "GameStateStackRequest.hpp"

class GameStateManager final : public GameStateChanger, private sf::NonCopyable
{
public:
	GameStateManager(GameContextData& gameContextData);

	template<typename TGameState>
	void registerState(const GameStateIdentifiers identifier);

	void pushState(const GameStateIdentifiers identifier);
	void popState();
	void clearStates();

	void pushStateRequest(const GameStateIdentifiers identifier) override;
	void popStateRequest() override;
	void clearStatesRequest() override;

	void executeRequests();

	void processEvents(const sf::Event& event);
	void processLogic(const sf::Time& frameTime);
	void processRender(sf::RenderTarget& renderTarget);

	std::size_t getActiveStateCount() const;

	bool hasActiveStates() const;

private:
	GameState* findState(const GameStateIdentifiers identifier) const;
	GameState* getActiveState() const;

	GameContextData& mGameContextData;
	std::unordered_map<GameStateIdentifiers, std::unique_ptr<GameState>> mGameStates;
	std::queue<std::unique_ptr<GameStateStackRequest>> mGameStateStackRequests;
	std::deque<GameState*> mGameStateStack;
};

template<typename TGameState>
inline void GameStateManager::registerState(const GameStateIdentifiers identifier)
{
	static_assert(std::is_base_of_v<GameState, TGameState>, "TGameState must derived from GameState");

	mGameStates.emplace(identifier, std::make_unique<TGameState>(mGameContextData, *this));
}
